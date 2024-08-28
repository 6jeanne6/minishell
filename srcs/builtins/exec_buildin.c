/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:43:09 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/27 20:56:14 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	/*
	if (ft_strcmp(exec->cmd_name, "echo") == 0)
		gear_5->exit_status = 
	*/
	if (ft_strcmp(exec->cmd_name, "cd") == 0)
		gear_5->exit_status = cd(envp, exec);
	/*
	if (ft_strcmp(exec->cmd_name, "pwd") == 0)
		gear_5->exit_status = 
	if (ft_strcmp(exec->cmd_name, "env") == 0)
		gear_5->exit_status = 
	if (ft_strcmp(exec->cmd_name, "export") == 0)
		gear_5->exit_status = 
	if (ft_strcmp(exec->cmd_name, "unset") == 0)
		gear_5->exit_status = 
	if (ft_strcmp(exec->cmd_name, "exit") == 0)
		gear_5->exit_status = 
	*/
}

