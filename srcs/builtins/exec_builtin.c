/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 09:43:09 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/05 14:29:52 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (ft_strcmp(exec->args[0], "echo") == 0)
		echo(gear_5, exec);
	if (ft_strcmp(exec->args[0], "cd") == 0)
		cd (gear_5, envp, exec);
	if (ft_strcmp(exec->args[0], "pwd") == 0)
		pwd(gear_5, envp, exec);
	if (ft_strcmp(exec->args[0], "env") == 0)
		env(gear_5, envp, exec);
	if (ft_strcmp(exec->args[0], "export") == 0)
		export(gear_5, envp, exec);
	if (ft_strcmp(exec->args[0], "unset") == 0)
		unset(gear_5, envp, exec);
	if (ft_strcmp(exec->args[0], "exit") == 0)
		exit_builtin(gear_5, envp, exec);

}

