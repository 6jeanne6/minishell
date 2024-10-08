/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:43:09 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/04 16:28:34 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execute builtin
int	exec_builtin(t_shell *gear_5, t_env *envp, t_exec *exec, t_exec *head)
{
	if (!exec || !envp || !gear_5 || !head)
		return (FAILURE);
	if (ft_strcmp(exec->args[0], "echo") == 0)
	{
		if (exec->has_pipe == false)
			return (echo(gear_5, exec), SUCCESS);
		else
			return (echo_pipe(gear_5, exec), SUCCESS);
	}
	if (ft_strcmp(exec->args[0], "cd") == 0)
		return (cd (gear_5, envp, exec), SUCCESS);
	if (ft_strcmp(exec->args[0], "pwd") == 0)
		return (pwd(gear_5, envp, exec), SUCCESS);
	if (ft_strcmp(exec->args[0], "env") == 0)
		return (env(gear_5, envp, exec), SUCCESS);
	if (ft_strcmp(exec->args[0], "export") == 0)
		return (export(gear_5, envp, exec), SUCCESS);
	if (ft_strcmp(exec->args[0], "unset") == 0)
		return (unset(gear_5, envp, exec), SUCCESS);
	if (ft_strcmp(exec->args[0], "exit") == 0)
		return (exit_builtin(gear_5, envp, exec, head), SUCCESS);
	return (FAILURE);
}
