/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:08:15 by jewu              #+#    #+#             */
/*   Updated: 2024/10/20 14:47:59 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_variables(t_var *var, t_env *envp, int fd_out)
{
	while (var)
	{
		if (envp->env_i_flag && ft_strcmp(var->variable_name, "PATH") == 0)
		{
			var = var->next;
			continue ;
		}
		ft_putstr_fd(var->variable_name, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(var->variable_value, fd_out);
		ft_putstr_fd("\n", fd_out);
		var = var->next;
	}
}

void	env_pipe(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	t_var	*var;

	if (!gear_5 || !envp)
		return ;
	if (exec->args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		gear_5->exit_status = 1;
		return ;
	}
	var = envp->first_variable;
	if (!var)
		return ;
	print_env_variables(var, envp, STDOUT_FILENO);
	gear_5->exit_status = 0;
}

void	env(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	t_var	*var;

	if (!gear_5 || !envp)
		return ;
	if (exec->args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		gear_5->exit_status = 1;
		return ;
	}
	var = envp->first_variable;
	if (!var)
		return ;
	print_env_variables(var, envp, exec->fd_out);
	gear_5->exit_status = 0;
}
