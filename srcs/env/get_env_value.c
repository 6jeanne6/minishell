/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:40:25 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/18 18:59:38 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_var_value_with_name(t_env *env, char *name, char *value)
{
	t_var	*var;

	var = find_variable_value_by_name(env, name);
	if (!var)
		return ;
	change_env_var_value(var, value);
}

void	change_env_var_value(t_var *var, char *new_value)
{
	if (var->variable_value != NULL)
	{
		free(var->variable_value);
	}
	var->variable_value = ft_strdup(new_value);
}
