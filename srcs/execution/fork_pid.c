/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:18:07 by jewu              #+#    #+#             */
/*   Updated: 2024/09/21 17:44:47 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle multi-pipes and dup2 with previous fd
static int	do_fork(t_shell *gear_5, t_exec *exec, t_env *envp, int cmd)
{
	int		i;
	int		status_code;
	t_exec	*current;
	t_exec	*head;

	i = -1;
	current = exec;
	head = exec;
	gear_5->j = 0;
	while (++i < cmd)
	{
		gear_5->pid_tab[i] = fork();
		if (gear_5->pid_tab[i] == -1)
			error_shell_exec(gear_5, envp, head);
		else if (gear_5->pid_tab[i] == 0)
			child_process(current, gear_5, envp, head);
		current = current->next;
		gear_5->j++;
	}
	close_pipe_tab(gear_5, cmd);
	status_code = get_status_code(gear_5, cmd);
	return (status_code);
}

//pipe tab initialization
static void	init_tab_pipe(t_shell *gear_5, t_exec *exec, t_env *envp, int cmd)
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
			error_shell_exec(gear_5, envp, exec);
		if (pipe(gear_5->pipe_tab[i]) == -1)
			error_shell_exec(gear_5, envp, exec);
	}
}

//creates pid into a tab
static void	init_tab_pid(t_shell *gear_5, t_exec *exec, t_env *envp, int cmd)
{
	if (!gear_5 || !exec)
		return ;
	gear_5->pid_tab = ft_calloc(cmd, sizeof(pid_t));
	if (!gear_5->pid_tab)
	{
		error_shell_exec(gear_5, envp, exec);
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
	int		commands;

	if (!gear_5 || !envp || !exec)
		return (FAILURE);
	commands = how_many_process(exec);
	exec->nb_cmd = commands;
	gear_5->number_of_cmds = commands;
	if (is_builtin(exec->cmd_name) == SUCCESS && exec->has_pipe == false)
	{
		if (exec_builtin(gear_5, envp, exec) == SUCCESS)
			return (3);
	}
	init_tab_pid(gear_5, exec, envp, commands);
	init_tab_pipe(gear_5, exec, envp, commands);
	gear_5->status_code = do_fork(gear_5, exec, envp, commands);
	return (SUCCESS);
}
