/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:36:11 by jewu              #+#    #+#             */
/*   Updated: 2024/09/24 14:58:28 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

//update parent exit status with last child status code
int	child_status_code(t_shell *gear_5)
{
	int	exit;

	exit = 0;
	if (!gear_5)
		return (FAILURE);
	if (gear_5->status_code == 2)
		exit = 2;
	else if (gear_5->status_code == 1)
		exit = 1;
	else if (gear_5->status_code == 126)
		exit = 126;
	else if (gear_5->status_code == 127)
		exit = 127;
	else if (gear_5->status_code == 0)
		exit = 0;
	else if (gear_5->status_code == 3)
		exit = 131;
	return (exit);
}

//get status code of the last child process
int	get_status_code(t_shell *gear_5, int cmd)
{
	int	i;
	int	status;
	int	last_status;

	if (!gear_5)
		return (FAILURE);
	i = -1;
	while (++i < cmd)
	{
		g_sig_flag = IN_CHILD;
		update_signal_exit(gear_5);
		waitpid(gear_5->pid_tab[i], &status, 0);
		if (i == cmd - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = WTERMSIG(status);
		}
	}
	g_sig_flag = IN_PARENT;
	return (last_status);
}

//close pipe tab in gear_5
void	close_pipe_tab(t_shell *gear_5, int cmd)
{
	int	i;

	if (!gear_5)
		return ;
	i = -1;
	while (++i < cmd - 1)
	{
		close(gear_5->pipe_tab[i][READ_END]);
		close(gear_5->pipe_tab[i][WRITE_END]);
	}
}
