/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/10/16 19:17:38 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//close all pipes
void	error_shell_exec(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!envp || !gear_5 || !exec)
		return ;
	clean_env(envp);
	if (exec->fd_in > 2)
		close(exec->fd_in);
	if (exec->fd_out > 2)
		close(exec->fd_out);
	clean_exec(exec, gear_5);
	free_exec(exec);
	close_heredoc(gear_5);
	close(STDIN_FILENO);
	exit(gear_5->exit_status);
}

//when execve succeed, clean everything and process can terminate
void	execve_clean_all(t_exec *exec, t_env *envp, t_shell *gear_5)
{
	if (!envp || !envp->env[0] || !gear_5)
		return ;
	clean_env(envp);
	close_files(exec, gear_5);
	clean_exec(exec, gear_5);
	free_exec(exec);
}

//close both end of pipe and free it
static void	close_and_free_pipe_tab(t_shell *gear_5)
{
	int	i;

	if (!gear_5)
		return ;
	i = -1;
	while (++i < gear_5->number_of_cmds - 1)
	{
		close(gear_5->pipe_tab[i][READ_END]);
		close(gear_5->pipe_tab[i][WRITE_END]);
		free(gear_5->pipe_tab[i]);
	}
	free(gear_5->pipe_tab);
	gear_5->pipe_tab = NULL;
}

//free pid tab
static void	free_pid_tab(t_shell *gear_5)
{
	if (!gear_5)
		return ;
	if (gear_5->pid_tab)
	{
		free(gear_5->pid_tab);
		gear_5->pid_tab = NULL;
	}
}

//free stuff in t_exec, and in gear_5 pid and pipe tab
void	clean_exec(t_exec *exec, t_shell *gear_5)
{
	t_exec	*current;

	if (!exec || !gear_5)
		return ;
	current = exec;
	free_pid_tab(gear_5);
	close_and_free_pipe_tab(gear_5);
	while (current)
	{
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->bin)
			free(current->bin);
		current = current->next;
	}
}
