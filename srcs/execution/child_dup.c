/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:38:41 by jewu              #+#    #+#             */
/*   Updated: 2024/09/09 13:38:43 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//first command:
// → use infile as STDIN
// → use current pipe as STDOUT
static void	first_dup(t_exec *exec, t_shell *gear_5)
{
	if (exec->fd_in < 0)
	{
		close(exec->fd_out);
		update_exit_status(gear_5, 1, NULL);
		return ;
	}
	dup2(exec->fd_in, STDIN_FILENO);
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

//last command:
// → reads previous pipe as STDIN
// → use outfile as STDOUT
static void	last_dup(t_exec *exec, t_shell *gear_5)
{
	dup2(exec->pipe_tab[gear_5->j - 1][READ_END], STDIN_FILENO);
	dup2(exec->fd_out, STDOUT_FILENO);
}

//child process when PID is equal to 0
//• read input from a file (pipefd[0]) and sent it to the pipe
void	child_process(t_exec *exec, t_shell *gear_5, t_env *envp, int cmd)
{
	int	i;

	i = -1;
	if (gear_5->j == 0)
		first_dup(exec, gear_5);
	else if (gear_5->j < cmd - 1)
		middle_dup(exec, gear_5);
	else
		last_dup(exec, gear_5);
	while (++i < cmd - 1)
	{
		close(exec->pipe_tab[i][READ_END]);
		close(exec->pipe_tab[i][WRITE_END]);
	}
	exit(SUCCESS);
}