/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:38:41 by jewu              #+#    #+#             */
/*   Updated: 2024/09/11 14:36:05 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//first command:
// → use infile as STDIN
// → use current pipe as STDOUT
static void	first_dup(t_exec *exec, t_shell *gear_5)
{
	if (exec->fd_in >= 0)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
		{
			update_exit_status(gear_5, 1, NULL);
			perror("dup2 failed on fd_in\n");
			return ;
		}
	}
	dup2(exec->pipe_tab[gear_5->j][WRITE_END], STDOUT_FILENO);
}

//middle commands:
// → reads previous pipe as STDIN
// → use current pipe as STDOUT
static void	middle_dup(t_exec *exec, t_shell *gear_5)
{
	dup2(exec->pipe_tab[gear_5->j - 1][READ_END], STDIN_FILENO);
	dup2(exec->pipe_tab[gear_5->j][WRITE_END], STDOUT_FILENO);
}

// last command:
// → reads previous pipe as STDIN
// → use outfile as STDOUT
static void	last_dup(t_exec *exec, t_shell *gear_5)
{
	dup2(exec->pipe_tab[gear_5->j - 1][READ_END], STDIN_FILENO);
	if (exec->fd_out >= 0)
	{
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
		{
			update_exit_status(gear_5, 1, NULL);
			perror("dup2 failed on fd_out\n");
			return ;
		}
	}
}

//child process when PID is equal to 0
//• read input from a file (pipefd[0]) and sent it to the pipe
void	child_process(t_exec *exec, t_shell *gear_5, t_env *envp, int cmd)
{
	int	i;

	i = -1;
	if (basic_fd(exec) == false || cmd > 1)
	{
		if (gear_5->j == 0)
			first_dup(exec, gear_5);
		else if (gear_5->j < cmd - 1)
			middle_dup(exec, gear_5);
		else
			last_dup(exec, gear_5);
	}
	while (++i < cmd - 1)
	{
		// if (i == gear_5->j)
		// 	continue ;
		close(exec->pipe_tab[i][READ_END]);
		close(exec->pipe_tab[i][WRITE_END]);
	}
	execve_all(gear_5, envp, exec);
	exit(SUCCESS);
}
