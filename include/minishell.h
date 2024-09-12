/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:16:46 by jewu              #+#    #+#             */
/*   Updated: 2024/09/12 18:55:19 by jewu             ###   ########.fr       */
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

	char			*cmd_name;
	char			*bin;

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
	char	*input;

	int		exit_status;
	int		j;

	int		**pipe_tab;

	pid_t	*pid_tab;

}				t_shell;

/****** GLOBAL ******/

extern int	g_signal_status;

/****** FUNCTIONS ******/

/* init minishell */

/* environment */

void	init_env(t_env *envp, char **env);
void	fetch_path(t_env *envp);

char	**copy_path(t_env *envp);
char	**split_path(t_env *envp, char *str);
char	**find_path(t_env *envp, char **str);

/* exit status */
int		update_exit_status_code(t_shell *gear_5);
int		is_dollar_question_mark_input(t_shell *gear_5);
int		update_exit_status(t_shell *gear_5, int flag, char *name);

/* builtins */
int		is_builtin(char *word);
void	exec_builtin(t_shell *gear_5, t_env *envp, t_exec *exec);
char	*get_current_path(void);
int		cd(t_env *envp, t_exec *exec, t_shell *gear_5);

//void		pwd(t_shell *gear_5);
//void		exit(t_shell *gear_5, t_exec *execution);
//void  	env(t_shell *gear_5, t_env *envp);

/* environnement variable */

t_var	*init_env_variable(char *name, char *value);

char	*malloc_substr_and_cpy(const char *original_str, int start, int end);
char	*get_variable_name(char *variable);
char	*get_variable_value(char *variable);

void	init_chained_var(t_env *env, char **envp);
void	add_variable_to_the_list(t_env *env, t_var *var);
void	free_var_list(t_env *env);

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
int		how_many_dollar(char *str);
int		pwd_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		env_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		export_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		unset_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		exit_ok(t_shell *gear_5, t_token *token, t_env *envp);
int		is_file(char *file);
void	extract_words(const char *line, t_token **head);
void	handle_characters(t_parsing *state, int word_length);
void	handle_variable(t_parsing *state, int word_length);
void	handle_special_char(t_parsing *state, int word_length);
void	handle_space(t_parsing *state, int word_length);
void	handle_quotes(t_parsing *state);
void	process_token(t_parsing *state, int word_length);

/* linked list management */

void	add_to_list(t_token **head, t_parsing *state,
			const char *word, int word_length);
void	appendright(t_token **head, t_token *new);
t_token	*ft_double_lstlast(t_token *lst);

/* expander $ */
void	expander(t_token *list, t_env *envp);
void	empty_string(t_token *list);
void	expand_content(t_token *list, t_env *envp);
void	variable_compute(char *word, int *i, int *j);

char	*create_new_word(t_token *list, t_env *envp, int len);
char	*ft_strndup(const char *s, size_t n);

int		substitute_compute(t_env *envp, char *word);
int		treatment(char *word, t_env *envp, char *new_word, int j);
int		get_var_value(t_env *envp, char *variable, char *new_word, int j);
int		is_in_list(t_env *envp, char *variable);

//t_token	init_struct(t_token *list, t_env *envp);

/* execution */

t_exec	*init_exec(t_shell *gear_5, t_token *token, t_env *envp);

int		file_outfile(t_shell *gear_5, t_exec *exec, t_token *token);
int		file_input(t_exec *exec, t_token *token);
int		set_fd(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp);
int		create_heredoc(t_exec *exec, t_token *token);
int		init_fork(t_shell *gear_5, t_env *envp, t_exec *exec);

bool	token_is_redirection(t_token *token);
bool	basic_fd(t_exec *exec);

void	set_arg_tab(t_exec *exec, t_token *token, t_env *envp, int arg_count);
void	fail_set_fd_clean(t_exec *exec);
void	child_process(t_exec *exec, t_shell *gear_5, t_env *envp, int cmd);
void	execve_all(t_shell *gear_5, t_env *envp, t_exec *exec);

//void	link_exec(t_exec *prev_exec, t_exec *exec);

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
void	close_files(t_exec *exec);

/* debug */

void	print_token_list(t_token *list);
void	print_token(t_token *token, int index);
void	print_exec_list(t_exec *exec, t_shell *gear_5);	

#endif