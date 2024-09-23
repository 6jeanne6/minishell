/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:08:15 by jewu              #+#    #+#             */
/*   Updated: 2024/09/20 15:44:11 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//env with no options or arguments
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
	while (var)
	{
		ft_putstr_fd(var->variable_name, exec->fd_out);
		ft_putstr_fd("=", exec->fd_out);
		ft_putstr_fd(var->variable_value, exec->fd_out);
		ft_putstr_fd("\n", exec->fd_out);
		var = var->next;
	}
	gear_5->exit_status = 0;
}
