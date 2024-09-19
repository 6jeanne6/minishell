/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:36:11 by jewu              #+#    #+#             */
/*   Updated: 2024/09/19 15:23:08 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		waitpid(gear_5->pid_tab[i], &status, 0);
		if (i == cmd - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
		}
	}
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
