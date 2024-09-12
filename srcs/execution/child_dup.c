/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:38:41 by jewu              #+#    #+#             */
/*   Updated: 2024/09/12 19:10:58 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//first command:
// → use infile as STDIN
// → use current pipe as STDOUT
static void	first_dup(t_exec *exec, t_shell *gear_5, t_env *envp, int cmd)
{
	if (exec->fd_in < 0)
	{
		close(exec->fd_out);
		error_shell_exec(gear_5, envp, exec);
	}
	if (cmd == 1 && exec->fd_out >= 0)
	{
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
		{
			update_exit_status(gear_5, 1, NULL);
			perror("dup2 failed on fd_out\n");
			return ;
		}
	}
	if (cmd > 1)
		dup2(gear_5->pipe_tab[gear_5->j][WRITE_END], STDOUT_FILENO);
	if (exec->fd_in >= 0)
	{
		if (dup2(exec->fd_in, STDIN_FILENO) == -1)
		{
			update_exit_status(gear_5, 1, NULL);
			perror("dup2 failed on fd_in\n");
			return ;
		}
	}
}

//middle commands:
// → reads previous pipe as STDIN
// → use current pipe as STDOUT
static void	middle_dup(t_exec *exec, t_shell *gear_5)
{
	(void)exec;
	dup2(gear_5->pipe_tab[gear_5->j - 1][READ_END], STDIN_FILENO);
	dup2(gear_5->pipe_tab[gear_5->j][WRITE_END], STDOUT_FILENO);
}

// last command:
// → reads previous pipe as STDIN
// → use outfile as STDOUT
static void	last_dup(t_exec *exec, t_shell *gear_5)
{
	dup2(gear_5->pipe_tab[gear_5->j - 1][READ_END], STDIN_FILENO);
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
			first_dup(exec, gear_5, envp, cmd);
		else if (gear_5->j < cmd - 1)
			middle_dup(exec, gear_5);
		else
			last_dup(exec, gear_5);
	}
	close_files(exec);
	while (++i < cmd - 1)
	{
		close(gear_5->pipe_tab[i][READ_END]);
		close(gear_5->pipe_tab[i][WRITE_END]);
	}
	execve_all(gear_5, envp, exec);
	exit(SUCCESS);
}
