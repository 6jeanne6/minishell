/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:33:09 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/16 15:23:29 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_chained_var(t_env *env, char **envp)
{
	t_var	*variable;
	char	*variable_name;
	char	*variable_value;
	int		index;

	index = 0;
	while (envp[index])
	{
		variable_name = get_variable_name(envp[index]);
		variable_value = get_variable_value(envp[index]);
		variable = init_env_variable(variable_name, variable_value);
		add_variable_to_the_list(env, variable);
		index++;
	}
}

t_var	*init_env_variable(char *name, char *value)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->variable_name = name;
	var->variable_value = value;
	var->next = NULL;
	var->prev = NULL;
	return (var);
}

void	add_variable_to_the_list(t_env *env, t_var *var)
{
	t_var	*current_var;

	if (!(env->first_variable))
	{
		env->first_variable = var;
	}
	else
	{
		current_var = env->first_variable;
		while (current_var->next)
			current_var = current_var->next;
		current_var->next = var;
	}
	var->next = NULL;
}

char	*get_variable_name(char *variable)
{
	int		i;
	int		j;
	char	*variable_name;

	i = 0;
	if (!variable)
		return (NULL);
	while (variable[i])
	{
		if (variable[i] == '=')
		{
			j = i - 1;
			variable_name = malloc_substr_and_cpy(variable, 0, j);
			return (variable_name);
		}
		i++;
	}
	j = i - 1;
	variable_name = malloc_substr_and_cpy(variable, 0, j);
	return (variable_name);
}

char	*get_variable_value(char *variable)
{
	int		i;
	int		j;
	int		k;
	char	*value_name;

	i = 0;
	if (!variable)
		return (NULL);
	while (variable[i])
	{
		if (variable[i] == '=')
		{
			j = i + 1;
			k = ft_strlen(variable) - 1;
			value_name = malloc_substr_and_cpy(variable, j, k);
			return (value_name);
		}
		i++;
	}
	return (NULL);
}
