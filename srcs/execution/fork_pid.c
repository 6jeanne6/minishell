/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:18:07 by jewu              #+#    #+#             */
/*   Updated: 2024/09/11 16:11:32 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle multi-pipes and dup2 with previous fd
static void	do_fork(t_shell *gear_5, t_exec *exec, t_env *envp, int cmd)
{
	int		i;
	t_exec	*current;

	i = -1;
	current = exec;
	while (++i < cmd)
	{
		gear_5->pid_tab[i] = fork();
		if (gear_5->pid_tab[i] == -1)
			error_shell_exec(gear_5, envp, current);
		else if (gear_5->pid_tab[i] == 0)
			child_process(current, gear_5, envp, cmd);
		current = current->next;
		gear_5->j++;
	}
	i = -1;
	while (++i < cmd - 1)
	{
		close(gear_5->pipe_tab[i][READ_END]);
		close(gear_5->pipe_tab[i][WRITE_END]);
	}
	i = -1;
	while (++i < cmd)
		waitpid(gear_5->pid_tab[i], 0, 0);
}

//pipe tab initialization
static void	init_tab_pipe(t_shell *gear_5, t_exec *exec, int cmd)
{
	int		i;

	i = -1;
	if (!exec || !gear_5)
		return ;
	gear_5->pipe_tab = ft_calloc(cmd - 1, sizeof(int *));
	if (!gear_5->pipe_tab)
	{
		update_exit_status(gear_5, 1, NULL);
		return ;
	}
	while (++i < cmd - 1)
	{
		gear_5->pipe_tab[i] = ft_calloc(2, sizeof(int));
		if (!gear_5->pipe_tab[i])
			clean_exec(exec, gear_5);
		if (pipe(gear_5->pipe_tab[i]) == -1)
			clean_exec(exec, gear_5);
	}
}

//creates pid into a tab
static void	init_tab_pid(t_shell *gear_5, t_exec *exec, int cmd)
{
	if (!gear_5 || !exec)
		return ;
	gear_5->pid_tab = ft_calloc(cmd, sizeof(pid_t));
	if (!gear_5->pid_tab)
	{
		clean_exec(exec, gear_5);
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
	int		commands;

	if (!gear_5 || !envp || !exec)
		return (FAILURE);
	current_process = exec;
	commands = how_many_process(current_process);
	exec->nb_cmd = commands;
	init_tab_pid(gear_5, current_process, commands);
	init_tab_pipe(gear_5, exec, commands);
	do_fork(gear_5, current_process, envp, commands);
	// gear_5->j = 0;
	// while (current_process)
	// {
	// 	do_fork(gear_5, current_process, envp, commands);
	// 	current_process = current_process->next;
	// 	gear_5->j++;
	// }
	return (SUCCESS);
}
