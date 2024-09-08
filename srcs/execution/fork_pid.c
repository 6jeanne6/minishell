/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:18:07 by jewu              #+#    #+#             */
/*   Updated: 2024/09/08 16:23:03 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle multi-pipes and dup2 with previous fd
static void	do_fork(t_shell *gear_5, t_env *envp, t_exec *exec, int cmd)
{
	int	i;

	i = -1;
	while (++i < cmd)
	{
		exec->pid_tab[i] = fork();
		if (exec->pid_tab[i] == -1)
		{
			update_exit_status(gear_5, 1, NULL);
			return ;
		}
		else if (exec->pid_tab[i] == 0)
			child_process(pipex, i, argv, env);
		i = -1;
		while (++i < cmd)
		{
			close(exec->pipe_tab[i][READ_END]);
			close(exec->pipe_tab[i][WRITE_END]);
		}
		i = -1;
		while (++i < cmd)
			waitpid(exec->pid_tab[i], 0, 0);
	}
}

//pipe tab initialization
static void	init_tab_pipe(t_shell *gear_5, t_env *envp, t_exec *exec, int cmd)
{
	int	i;

	i = -1;
	exec->pipe_tab = ft_calloc(cmd, sizeof(int *));
	if (!exec->pipe_tab)
	{
		update_exit_status(gear_5, 1, NULL);
		return ;
	}
	while (++i < cmd)
	{
		exec->pipe_tab[i] = ft_calloc(2, sizeof(int));
		if (!exec->pipe_tab[i])
			clean_exec(exec);
		if (pipe(exec->pipe_tab[i]) == -1)
			clean_exec(exec);
	}
}

//creates pid into a tab
static void	init_tab_pid(t_shell *gear_5, t_env *envp, t_exec *exec, int cmd)
{
	if (!gear_5 || !envp || !exec)
		return ;
	exec->pid_tab = ft_calloc(cmd, sizeof(pid_t));
	if (!exec->pid_tab)
	{
		clean_exec(exec);
		update_exit_status(gear_5, 1, NULL);
		return ;
	}
}

//compute how many commands/builtins to determine how many pid needed
static int	how_many_process(t_exec *exec)
{
	int	number_of_commands;

	number_of_commands = 0;
	if (!exec)
		return (number_of_commands);
	while (exec)
	{
		number_of_commands++;
		exec = exec->next;
	}
	return (number_of_commands);
}

//creates fork
int	init_fork(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	t_exec	*current_process;
	t_exec	*start;
	int		commands;

	if (!gear_5 || !envp || !exec)
		return (FAILURE);
	current_process = exec;
	start = exec;
	commands = how_many_process(start);
	exec->nb_cmd = commands;
	init_tab_pid(gear_5, envp, exec, commands);
	init_tab_pipe(gear_5, envp, exec, commands);
	do_fork(gear_5, envp, exec, commands);
	while (current_process)
	{
		current_process = current_process->next;
	}
	return (SUCCESS);
}
