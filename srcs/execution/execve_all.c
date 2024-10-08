/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:39:54 by jewu              #+#    #+#             */
/*   Updated: 2024/10/08 15:21:39 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_bin(t_exec *exec)
{
	if (!exec)
		return (FAILURE);
	if (exec->bin)
	{
		if (access(exec->bin, X_OK) == 0)
			return (SUCCESS);
	}
	return (42);
}

//execute programs like ./minishell
static void	execve_executable_program(t_shell *gear_5, t_env *envp,
t_exec *exec)
{
	if (!gear_5 || !envp || !exec)
		return ;
	execve(exec->cmd_name, exec->args, envp->env);
	if (execve(exec->cmd_name, exec->args, envp->env) < 0)
	{
		update_exit_status(gear_5, 126, exec->cmd_name);
		error_close_files(exec, gear_5);
		execve_clean_all(exec, envp, gear_5);
		exit(126);
	}
	execve_clean_all(exec, envp, gear_5);
	exit(SUCCESS);
}

//if bin execute absolute path and bin command
static void	execve_bin(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (exec->cmd_name[0] == '/')
	{
		execve(exec->bin, exec->args, envp->env);
		if (execve(exec->bin, exec->args, envp->env) <= -1)
		{
			update_exit_status(gear_5, 127, exec->cmd_name);
			error_close_files(exec, gear_5);
			execve_clean_all(exec, envp, gear_5);
			exit(127);
		}
	}
	else
	{
		execve(exec->bin, exec->args, envp->env);
		if (execve(exec->bin, exec->args, envp->env) < 0)
		{
			update_exit_status(gear_5, 126, exec->cmd_name);
			error_close_files(exec, gear_5);
			execve_clean_all(exec, envp, gear_5);
			exit(126);
		}
	}
	execve_clean_all(exec, envp, gear_5);
}

//if builtin execute this
static void	execve_builtin(t_shell *gear_5, t_env *envp, t_exec *exec,
t_exec *head)
{
	if (!gear_5 || !envp || !exec)
		return ;
	if (exec_builtin(gear_5, envp, exec, head) == SUCCESS)
	{
		close_files(exec, gear_5);
		execve_clean_all(head, envp, gear_5);
		exit(SUCCESS);
	}
	else
	{
		update_exit_status(gear_5, 1, exec->cmd_name);
		error_close_files(exec, gear_5);
		execve_clean_all(head, envp, gear_5);
		exit(1);
	}
}

//execute
//	→ builtin: echo, unset...
//	→ binary command : ls, wc...
//  → executable program : ./minishell...
void	execve_all(t_shell *gear_5, t_env *envp, t_exec *exec, t_exec *head)
{
	if (!gear_5 || !envp || !exec || !head)
		return ;
	if (is_builtin(exec->cmd_name) == SUCCESS)
		execve_builtin(gear_5, envp, exec, head);
	if (exec->bin)
		execve_bin(gear_5, envp, exec);
	if (access(exec->cmd_name, X_OK) == 0)
		execve_executable_program(gear_5, envp, exec);
	else
	{
		update_exit_status(gear_5, 127, exec->cmd_name);
		error_close_files(exec, gear_5);
		execve_clean_all(exec, envp, gear_5);
		exit(127);
	}
}
