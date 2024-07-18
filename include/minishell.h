/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:16:46 by jewu              #+#    #+#             */
/*   Updated: 2024/07/18 19:32:51 by jewu             ###   ########.fr       */
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

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW 	"\033[0;33m"
# define BLUE 		"\033[0;34m"
# define PURPLE 	"\033[0;35m"
# define CYAN 		"\033[0;36m"
# define RESET 		"\033[0m"

/****** STRUCTURES ******/

typedef struct s_var
{
	char			*variable_name;
	char			*variable_value;
	struct s_var	*next;
	struct s_var	*prev;

}	t_var;

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
char	**copy_path(t_env *envp);
char	**split_path(t_env *envp, char *str);
char	**find_path(t_env *envp, char **str);
void	fetch_path(t_env *envp);

/* builtins */

char	*get_current_path(void);

/* environnement variable */

bool	is_variable(const char *input);
bool	is_variable_declaration(const char *input);
char	*malloc_substr_and_cpy(const char *original_str, int start, int end);
void	init_chained_var(t_env *env, char **envp);
t_var	*init_env_variable(char *name, char *value);
void	add_variable_to_the_list(t_env *env, t_var *var);
char	*get_variable_name(char *variable);
char	*get_variable_value(char *variable);
void	free_var_list(t_env *env);

/* lexing */

int		check_redirection(char *input);
int		check_variable(char *input, bool has_quotes);
int		check_pipe(char *input);
int		i_am_delimitor(char c);
int		check_quotes(char *input);
int		is_pipe(char *input);
int		check_special_characters(char *input);

/* parsing */

int		lexing_gear_5(t_shell *gear_5);
int		separator(t_shell *gear_5, t_env *envp);

/* error & free */

void	error(char	*message);
void	clean_env(t_env *envp);

#endif