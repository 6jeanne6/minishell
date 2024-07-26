/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:16:46 by jewu              #+#    #+#             */
/*   Updated: 2024/07/26 16:58:46 by jewu             ###   ########.fr       */
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

//#define MAX_WORD_LENGTH 256

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW 	"\033[0;33m"
# define BLUE 		"\033[0;34m"
# define PURPLE 	"\033[0;35m"
# define CYAN 		"\033[0;36m"
# define RESET 		"\033[0m"

/****** STRUCTURES ******/

typedef struct s_token
{
	char			*word;

	int				outer_double_quote;
	int				outer_single_quote;

	struct s_token	*previous;
	struct s_token	*next;
}				t_token;

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

typedef struct s_var
{
	char			*variable_name;
	char			*variable_value;
	struct s_var	*next;
	struct s_var	*prev;

}				t_var;

typedef struct s_quotes
{
	int		nbofsingle;
	int		nbofdouble;
	int		inside_double_quotes;
	int		inside_single_quotes;
}				t_quotes;

typedef struct s_env
{
	char	**env;
	char	**env_tmp;
	char	**path;
	char	*oldpwd;
	char	*pwd;
	t_var	*first_variable;
}				t_env;

typedef struct s_shell
{
	char	**path;
	char	**cmd;

	char	*input;
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

/* builtins */

char	*get_current_path(void);

/* environnement variable */

t_var	*init_env_variable(char *name, char *value);

bool	is_variable(const char *input);
bool	is_variable_declaration(const char *input);

char	*malloc_substr_and_cpy(const char *original_str, int start, int end);
char	*get_variable_name(char *variable);
char	*get_variable_value(char *variable);

void	init_chained_var(t_env *env, char **envp);
void	add_variable_to_the_list(t_env *env, t_var *var);
void	free_var_list(t_env *env);

/* lexing */

int		check_redirection(char *input);
int		check_variable(char *input, bool has_quotes);
int		check_pipe(char *input);
int		i_am_delimitor(char c);
int		check_quotes(char *input);
int		is_pipe(char *input);
int		check_special_characters(char *input);
int		ft_ispace(char c);

char	is_special_char(char c);

/* parsing */

int		lexing_gear_5(t_shell *gear_5);

void	extract_words(const char *line, t_token **head);
void	handle_characters(t_parsing *state, int word_length);
void	handle_variable(t_parsing *state, int word_length);
void	handle_special_char(t_parsing *state, int word_length);
void	handle_space(t_parsing *state, int word_length);
void	handle_quotes(t_parsing *state);
void	add_to_list(t_token **head, t_parsing *state,
			const char *word, int word_length);
void	appendright(t_token **head, t_token *new);

t_token	*ft_double_lstlast(t_token *lst);

/* error & free */

void	error(char	*message);
void	clean_env(t_env *envp);
void	free_token_list(t_token *head);

#endif