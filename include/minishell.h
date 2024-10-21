/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:16:46 by jewu              #+#    #+#             */
/*   Updated: 2024/10/20 14:52:44 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/****** INCLUDES ******/

# include "libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <term.h>
# include <termios.h>

/****** DEFINE ******/

# define FAILURE 	-1
# define SUCCESS 	0

//pipe[0] and pipe[1]
# define READ_END	0
# define WRITE_END	1

/****** COLORS ********/

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW 	"\033[0;33m"
# define BLUE 		"\033[0;34m"
# define PURPLE 	"\033[0;35m"
# define CYAN 		"\033[0;36m"
# define RESET 		"\033[0m"
# define WHITE      "\033[0;37m"

/***** TOKEN TYPE *******/

# define TOKEN_CMD        			1
# define TOKEN_ARG        			2
# define TOKEN_PIPE       			3
# define TOKEN_INPUT      			4
# define TOKEN_OUTPUT     			5
# define TOKEN_APPEND     			6
# define TOKEN_HEREDOC    			7
# define TOKEN_VARIABLE   			8
# define TOKEN_FILE       			9
# define TOKEN_UNKNOWN   			10
# define TOKEN_VARIABLEASSIGNATION	11
# define TOKEN_BUILTIN 				12

/****** STRUCTURES ******/

//execution structure
typedef struct s_exec
{
	struct s_exec	*prev;
	struct s_exec	*next;

	int				id;
	int				nb_cmd;
	int				in_double_quote;
	int				outer_double_quote;
	int				outer_single_quote;
	int				fd_in;
	int				fd_out;
	int				heredoc_state;

	char			*cmd_name;
	char			*bin;
	char			*heredoc_file;

	bool			heredoc_here;
	bool			has_pipe;

	char			**args;

}			t_exec;

//token
typedef struct s_token
{
	bool			has_heredoc;

	void			*class;

	char			*word;
	char			*cmd_path;

	struct s_token	*previous;
	struct s_token	*next;

	int				token_type;
	int				in_double_quote;
	int				outer_double_quote;
	int				outer_single_quote;

	int				*index;
}				t_token;

//parsing state
typedef struct s_parsing
{
	char	*line;
	char	*current_word;

	int		i;
	int		j;
	int		in_double_quote;
	int		in_single_quote;
	int		outer_double_quote;
	int		outer_single_quote;

	t_token	**token_list;
}				t_parsing;

//environment variable $
typedef struct s_var
{
	char			*variable_name;
	char			*variable_value;

	struct s_var	*next;
	struct s_var	*prev;

}				t_var;

//quotes ' or "
typedef struct s_quotes
{
	int		nbofsingle;
	int		nbofdouble;
	int		inside_double_quotes;
	int		inside_single_quotes;
}				t_quotes;

//set environment or create env
typedef struct s_env
{
	int		env_i_flag;
	char	**env;
	char	**env_tmp;
	char	**path;
	char	*oldpwd;

	char	*pwd;
	char	*cmd_path;
	char	*tmp_path;

	t_var	*first_variable;
}				t_env;

//shell with readline input and exit status
typedef struct s_shell
{
	bool	interrupted;

	char	*input;
	char	*delimiter;
	char	*last_input;

	char	**heredoc_tab;

	int		exit_status;
	int		status_code;
	int		j;
	int		number_of_cmds;
	int		number_of_hd;
	int		h_index;

	int		**pipe_tab;

	pid_t	*pid_tab;
	pid_t	here_doc_pid;

}				t_shell;

//struct to handle expand
typedef struct s_expand
{
	int			i;
	int			j;
	int			inside_double_quotes;
	int			inside_single_quotes;
	int			line_len;

	char		*expanded_line;

	t_env		*env;

	const char	*line;
}				t_expand;

/****** GLOBAL ******/

extern int	g_signal_status;

/****** FUNCTIONS ******/

/* Start */
int		processing_minishell(t_shell *gear_5, t_env *envp,
			t_exec **exec, int *flag);
int		init_minishell(t_shell *gear_5, t_env *envp);

void	reinit_everything(t_shell *gear_5, t_exec **exec);

/* environment */

void	init_env(t_env *envp, char **env);
void	fetch_path(t_env *envp);

char	**copy_path(t_env *envp);
char	**split_path(t_env *envp, char *str);
char	**find_path(t_env *envp, char **str);

/* exit status */

int		is_dollar_question_mark_input(t_shell *gear_5, int *flag);
int		update_exit_status(t_shell *gear_5, int flag, char *name);

/* signals */

void	handle_signal(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	sigint_here_doc(int sig);
void	sigint_reset(t_shell *gear_5);
void	handle_sig_in_fork(t_shell *gear_5, int cmd);
void	exit_ctrl_d(t_shell *gear_5, t_exec *exec, t_env *envp);

/* builtins */

t_var	*find_variable_by_name(t_env *env, char *name);
t_var	*get_first_env_var(t_env *env);

int		echo(t_shell *gear_5, t_exec *exec);
int		echo_pipe(t_shell *gear_5, t_exec *exec);
int		cd(t_shell *gear_5, t_env *envp, t_exec *exec);
int		pwd(t_shell *gear_5, t_env *envp, t_exec *exec);
int		export(t_shell *gear_5, t_env *envp, t_exec *exec);
int		unset(t_shell *gear_5, t_env *envp, t_exec *exec);
int		is_builtin(char *word);
int		is_valid_identifier(char *name, t_shell *gear_5, int code);
int		exec_builtin(t_shell *gear_5, t_env *envp, t_exec *exec, t_exec *head);
int		check_var_name(char *str);
int		is_num_overflow(char *str);

void	env(t_shell *gear_5, t_env *envp, t_exec *exec);
void	env_pipe(t_shell *gear_5, t_env *envp, t_exec *exec);
void	exit_builtin(t_shell *gear_5, t_env *envp, t_exec *exec, t_exec *head);
void	change_env_var_value_with_name(t_env *env, char *name, char *value);
void	change_env_var_value(t_var *var, char *new_value);
void	quit_if_exit_arg_is_not_numeric(char *str, t_shell *gear_5,
			t_env *envp, t_exec *exec);
void	unset_path(t_env *envp);
void	handle_path(t_env *envp, char *arg);

char	*get_current_path(void);
char	*get_env_var_value_with_name(t_env *env, char *name);

/* environnement variable */

t_var	*init_env_variable(char *name, char *value);

char	*malloc_substr_and_cpy(const char *original_str, int start, int end);
char	*get_variable_name(char *variable);
char	*get_variable_value(char *variable);
char	*malloc_strcpy(char *origin);

void	init_chained_var(t_env *env, char **envp);
void	add_variable_to_the_list(t_env *env, t_var *var);
void	free_var_list(t_env *env);
char	*double_array_to_one_array(char **path);
char	*trim_path(char const *s1, char const *set);

/* lexing */

int		check_redirection(char *input);
int		check_pipe(char *input);
int		i_am_delimitor(char c);
int		check_quotes(char *input);
int		is_pipe(char *input);
int		check_special_characters(char *input);
int		ft_ispace(char c);

char	is_special_char(char c);

/* parsing */

int		lexing_gear_5(t_shell *gear_5);
int		get_token_type(t_env *envp, t_token *token);
int		check_path(t_env *envp, t_token *token);
int		is_variable(const char *input);
int		is_variable_declaration(const char *input);
int		token_order(t_shell *gear_5, t_token *token);
int		builtin_order(t_shell *gear_5, t_token *token, t_env *envp);
int		pwd_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		env_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		export_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		unset_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		exit_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		pipe_order(t_token *token, t_shell *gear_5);
void	handle_single_quote(t_quotes *quotes);
void	extract_words(const char *line, t_token **head,
			t_env *envp, t_shell *gear_5);
void	handle_characters(t_parsing *state, int word_length);
void	handle_variable(t_parsing *state, int word_length);
void	handle_special_char(t_parsing *state, int word_length);
void	handle_space(t_parsing *state, int word_length);
void	handle_quotes(t_parsing *state);
void	process_token(t_parsing *state, int word_length);
void	handle_double_quote(t_quotes *quotes);
bool	token_is_a_redirection(t_token *token);
bool	token_is_dir(char *path);
void	handle_double_quote(t_quotes *quotes);

/* linked list management */

void	add_to_list(t_token **head, t_parsing *state,
			const char *word, int word_length);
void	appendright(t_token **head, t_token *new);

t_token	*ft_double_lstlast(t_token *lst);

/* expander $ */

char	*expander_test(t_env *env, const char *line, t_shell *shell);

int		is_valid_character(char c, t_expand *xpd);
int		ft_isspace(char c);
int		find_double_angle_brackets(const char *line);

char	*ft_strcpy(char *dest, const char *src);
char	*extract_variable_name(const char *line, int start, int end);
char	*check_in_the_list(char *name, t_env *env);

void	expand_exit_status(t_expand *expand, t_shell *gear_5);
void	handle_variable_in_list(t_expand *expand, char *var_name);
void	expand_variable(t_expand *xpd, t_shell *shell);
void	handle_q(t_expand *expand);
void	expander_two(t_env *env, t_shell *gear_5, t_token **list);

int		handle_variable_length(const char *line, int *i, t_env *env);
int		count_new_len(const char *line, t_env *env);

/* execution */

t_exec	*init_exec(t_shell *gear_5, t_token *token, t_env *envp);

int		file_outfile(t_shell *gear_5, t_exec *exec, t_token *token);
int		file_input(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp);
int		set_fd(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp);
int		create_heredoc(t_exec *exec, t_token *token, t_shell *gear_5);
int		init_fork(t_shell *gear_5, t_env *envp, t_exec *exec);
int		get_status_code(t_shell *gear_5, int cmd);
int		child_status_code(t_shell *gear_5);
int		valid_bin(t_exec *exec);
int		valid_executable(t_shell *gear_5, char *cmd_name);
int		is_dir(char *path, t_shell *gear_5);

bool	token_is_redirection(t_token *token);
bool	basic_fd(t_exec *exec);

void	set_arg_tab(t_exec *exec, t_token *token, t_env *envp, int arg_count);
void	fail_set_fd_clean(t_exec *exec);
void	child_process(t_exec *exec, t_shell *gear_5, t_env *envp, t_exec *head);
void	execve_all(t_shell *gear_5, t_env *envp, t_exec *exec, t_exec *head);
void	close_pipe_tab(t_shell *gear_5, int cmd);

/* error & free */

void	error(char	*message);
void	clean_env(t_env *envp);
void	free_token_list(t_token *head);
void	free_exec(t_exec *exec);
void	wrong_token_order(t_token *token, t_env *envp, t_shell *gear_5);
void	free_envp_path(t_env *envp);
void	free_t_exec(t_token *token, t_env *envp);
void	free_args_tab(char **argv);
void	super_free_token_list(t_token *head);
void	filename_error(char *name, char *message, t_shell *gear_5, int flag);
void	clean_exec(t_exec *exec, t_shell *gear_5);
void	execve_clean_all(t_exec *exec, t_env *envp, t_shell *gear_5);
void	error_shell_exec(t_shell *gear_5, t_env *envp, t_exec *exec);
void	close_files(t_exec *exec, t_shell *gear_5);
void	error_close_files(t_exec *exec, t_shell *gear_5);
void	invalid_fd_pipe(t_exec *exec, t_shell *gear_5, t_env *envp,
			t_exec *head);
void	close_heredoc(t_shell *gear_5);
void	clean_heredoc(char *delimiter, char *heredoc_name,
			t_exec *exec, t_shell *gear_5);
void	close_redir_fd(t_exec *exec);
void	set_fd_has_failed(t_exec *exec, t_shell *gear_5);
void	init_exec_clean(t_exec *exec);
void	cleanup_exec(t_exec **exec, t_shell *gear_5);

/* debug */

// void	print_token_list(t_token *list);
// void	print_token(t_token *token, int index);
//void	print_exec_list(t_exec *exec, t_shell *gear_5);	

#endif