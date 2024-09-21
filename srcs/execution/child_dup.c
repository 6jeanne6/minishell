/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:38:41 by jewu              #+#    #+#             */
/*   Updated: 2024/09/20 15:30:50 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//first command:
// → use infile as STDIN
// → use current pipe as STDOUT
// → invalid fd_in = free envp, exec and EXIT FAILURE
static void	first_dup(t_exec *exec, t_shell *gear_5, t_env *envp)
{
	if (exec->fd_in < 0)
		error_shell_exec(gear_5, envp, exec);
	if (gear_5->number_of_cmds == 1 && exec->fd_out >= 0)
	{
		if (dup2(exec->fd_out, STDOUT_FILENO) == -1)
		{
			update_exit_status(gear_5, 1, NULL);
			perror("dup2 failed on fd_out\n");
			return ;
		}
	}
	if (gear_5->number_of_cmds > 1)
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
void	child_process(t_exec *exec, t_shell *gear_5, t_env *envp, t_exec *head)
{
	int	i;

	i = -1;
	if (basic_fd(exec) == false || gear_5->number_of_cmds > 1)
	{
		if (gear_5->j == 0)
			first_dup(exec, gear_5, envp);
		else if (gear_5->j < gear_5->number_of_cmds - 1)
			middle_dup(exec, gear_5);
		else
			last_dup(exec, gear_5);
	}
	close_files(head);
	while (++i < gear_5->number_of_cmds - 1)
	{
		close(gear_5->pipe_tab[i][READ_END]);
		close(gear_5->pipe_tab[i][WRITE_END]);
	}
	execve_all(gear_5, envp, exec, head);
	exit(SUCCESS);
}
