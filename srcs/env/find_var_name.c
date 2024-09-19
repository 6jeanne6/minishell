/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:40:27 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/11 10:41:49 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*find_variable_by_name(t_env *env, char *name)
{
	t_var *current;

	current = env->first_variable;
	while (current != NULL)
	{
		if (strcmp(current->variable_name, name) == 0)
		{
			return (current);
		}
		current = current->next;
	}

	return (NULL);
}

t_var	*find_variable_value_by_name(t_env *env, char *name)
{
	t_var *current;

	current = env->first_variable;
	while (current != NULL)
	{
		if (ft_strcmp(current->variable_name, name) == 0)
		{
			return (current);
		}
		current = current->next;
	}

	return (NULL);
}
char	*get_env_var_value_with_name(t_env *env, char *name)
{
	t_var	*var;

	var = get_first_env_var(env);
	if (!var)
		return (NULL);
	while (var)
	{
		if (ft_strcmp(var->variable_name, name))
		{
			return (var->variable_value);
		}
		var = var->next;
	}
	return (NULL);
}
t_var	*get_first_env_var(t_env *env)
{
	if (env->first_variable)
		return (env->first_variable);
	return (0);
}
