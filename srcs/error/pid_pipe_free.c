/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/09/20 15:31:01 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//close all pipes
void	error_shell_exec(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!envp || !gear_5 || !exec)
		return ;
	clean_env(envp);
	clean_exec(exec, gear_5);
	free_exec(exec);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

//when execve succeed, clean everything and process can terminate
void	execve_clean_all(t_exec *exec, t_env *envp, t_shell *gear_5)
{
	if (!envp || !gear_5)
		return ;
	clean_env(envp);
	close_files(exec);
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
