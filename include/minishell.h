/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:16:46 by jewu              #+#    #+#             */
/*   Updated: 2024/07/15 19:28:36 by jewu             ###   ########.fr       */
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

typedef enum s_type
{
	PIPE,
	QUOTE,
	APPEND,
	HEREDOC,
	INPUT_REDIR,
	OUTPUT_REDIR,
	WORD,
}				t_type;

typedef struct s_token
{
	struct s_token	*previous;
	struct s_token	*next;

	t_type			*type;

	int				index;

	char			*content;
}				t_token;

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
	char	*user;
}				t_env;

typedef struct s_shell
{
	char	**path;
	char	**cmd;

	char	*input;
}				t_shell;

/****** GLOBAL ******/

//extern int	g_signal_status;

/****** FUNCTIONS ******/

/* init minishell */

/* init environment */

char	**copy_path(t_env *envp);
char	**split_path(t_env *envp, char *str);
char	**find_path(t_env *envp, char **str);

void	fetch_path(t_env *envp);

/* lexing */

int		is_redirection(char *input);
int		check_quotes(char *input);
int		is_pipe(char *input);
int		check_special_characters(char *input);
int		i_am_delimitor(char *str, t_env *envp);

/* parsing */

int		lexing_gear_5(t_shell *gear_5, t_env *envp);
int		tokenizer(t_shell *gear_5, t_env *envp);

/* error & free */

void	clean_env(t_env *envp);
void	error(t_env *envp, char *message);

#endif