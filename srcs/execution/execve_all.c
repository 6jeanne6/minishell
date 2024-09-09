/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:39:54 by jewu              #+#    #+#             */
/*   Updated: 2024/09/09 19:07:17 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execute command
void	execve_all(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!exec)
		return ;
	if (is_builtin(exec->cmd_name) == SUCCESS)
	{	
		exec_builtin(gear_5, envp, exec);
		execve_clean_all(exec, envp, gear_5);
		exit(SUCCESS);
	}
	if (exec->bin)
	{
		execve(exec->bin, exec->args, envp->env);
		if (execve(exec->bin, exec->args, envp->env) < 0)
		{
			update_exit_status(gear_5, 1, exec->cmd_name);
			exit(1);
		}
		execve_clean_all(exec, envp, gear_5);
		exit(SUCCESS);
	}
	else
	{
		update_exit_status(gear_5, 127, NULL);
		execve_clean_all(exec, envp, gear_5);
		exit(127);
	}
}
