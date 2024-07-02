/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:16:46 by jewu              #+#    #+#             */
/*   Updated: 2024/07/02 15:16:14 by jewu             ###   ########.fr       */
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

# define EXIT_FAILURE -1
# define EXIT_SUCCESS 0

/****** STRUCTURES ******/

typedef struct s_shell
{
	char	**path;
	char	**cmd;
}				t_shell;

/****** GLOBAL ******/

extern int	signal_status;

/****** FUNCTIONS ******/

/* init minishell */

//int	ft_boncourage(void);

#endif