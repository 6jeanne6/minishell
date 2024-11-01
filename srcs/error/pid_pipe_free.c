/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothin <lothin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/10/23 14:24:41 by lothin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//close both end of pipe and free it
static void	close_and_free_pipe_tab(t_shell *gear_5)
{
	int	i;

	if (!gear_5)
		return ;
	i = -1;
	if (gear_5->pipe_tab)
	{
		while (++i < gear_5->number_of_cmds - 1)
		{
			close(gear_5->pipe_tab[i][READ_END]);
			close(gear_5->pipe_tab[i][WRITE_END]);
			free(gear_5->pipe_tab[i]);
		}
		free(gear_5->pipe_tab);
		gear_5->pipe_tab = NULL;
	}
}

//close all pipes
void	error_shell_exec(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	t_exec	*current;

	if (!envp || !gear_5 || !exec)
		return ;
	current = exec;
	clean_env(envp);
	close_and_free_pipe_tab(gear_5);
	while (current)
	{
		if (current->fd_in > 2)
			close(current->fd_in);
		if (current->fd_out > 2)
			close(current->fd_out);
		current = current->next;
	}
	clean_exec(exec, gear_5);
	free_exec(exec);
	close_heredoc(gear_5);
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
	if (gear_5->input)
		free(gear_5->input);
	rl_clear_history();
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
	close_and_free_pipe_tab(gear_5);
	free_pid_tab(gear_5);
	while (current)
	{
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->bin)
			free(current->bin);
		current = current->next;
	}
}
