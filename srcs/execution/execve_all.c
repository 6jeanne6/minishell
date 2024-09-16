/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:39:54 by jewu              #+#    #+#             */
/*   Updated: 2024/09/16 18:39:01 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		error_close_files(exec);
		execve_clean_all(exec, envp, gear_5);
		exit(126);
	}
}

//if bin execute absolute path and bin command
static void	execve_bin(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!gear_5 || !envp || !exec)
		return ;
	if (exec->cmd_name[0] == '/')
	{
		execve(exec->bin, exec->args, envp->env);
		if (execve(exec->bin, exec->args, envp->env) <= -1)
		{
			update_exit_status(gear_5, 126, exec->cmd_name);
			error_close_files(exec);
			execve_clean_all(exec, envp, gear_5);
			exit(126);
		}
	}
	else
	{
		execve(exec->bin, exec->args, envp->env);
		if (execve(exec->bin, exec->args, envp->env) < 0)
		{
			update_exit_status(gear_5, 126, exec->cmd_name);
			error_close_files(exec);
			execve_clean_all(exec, envp, gear_5);
			exit(126);
		}
	}
	execve_clean_all(exec, envp, gear_5);
}

//if builtin execute this
static void	execve_builtin(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!gear_5 || !envp || !exec)
		return ;
	exec_builtin(gear_5, envp, exec);
	execve_clean_all(exec, envp, gear_5);
	exit(SUCCESS);
}

//execute
//	→ builtin: echo, unset...
//	→ binary command : ls, wc...
//  → executable program : ./minishell...
void	execve_all(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!exec)
		return ;
	if (is_builtin(exec->cmd_name) == SUCCESS)
		execve_builtin(gear_5, envp, exec);
	if (exec->bin)
		execve_bin(gear_5, envp, exec);
	if (access(exec->cmd_name, X_OK) == 0)
		execve_executable_program(gear_5, envp, exec);
	else
	{
		update_exit_status(gear_5, 127, exec->cmd_name);
		error_close_files(exec);
		execve_clean_all(exec, envp, gear_5);
		exit(127);
	}
}
