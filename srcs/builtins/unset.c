/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:14:54 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/16 15:29:12 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free var nodes */
static void	free_env_var(t_var *var)
{
	if (var)
	{
		if (var->variable_name)
			free(var->variable_name);
		if (var->variable_value)
			free(var->variable_value);
		free(var);
	}
}

/* Disconnect variable from the list and reconnect the list */
static void	disconnect_env_var(t_env *env, t_var *var)
{
	t_var	*var_prev;
	t_var	*var_next;

	var_prev = var->prev;
	var_next = var->next;
	if (var_prev)
		var_prev->next = var_next;
	if (var_next)
		var_next->prev = var_prev;
	if (var == env->first_variable)
		env->first_variable = var_next;
	var->next = NULL;
	var->prev = NULL;
}

/* Unset all variables if they exist */
static void	unset_variable(t_env *env, char *name)
{
	t_var	*var;

	var = env->first_variable;
	while (var)
	{
		if (ft_strcmp(var->variable_name, name) == 0)
		{
			disconnect_env_var(env, var);
			free_env_var(var);
			return ;
		}
		var = var->next;
	}
}

/* Check all arguments after unset */
int	unset(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	char	*name;
	int		i;

	if (!exec->args[1])
	{
		gear_5->exit_status = 0;
		return (0);
	}
	i = 1;
	while (exec->args[i])
	{
		name = get_variable_name(exec->args[i]);
		if (is_valid_identifier(name, gear_5, 2) == FAILURE)
			return (FAILURE);
		unset_variable(envp, name);
		free(name);
		i++;
	}
	gear_5->exit_status = 0;
	return (0);
}
