/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:40:25 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/27 17:11:57 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change name
void	change_env_var_value_with_name(t_env *env, char *name, char *value)
{
	t_var	*var;

	if (!env || !name || !value)
		return ;
	var = find_variable_by_name(env, name);
	if (!var && ft_strcmp(name, "PWD") == 0)
	{
		var = init_env_variable(ft_strdup(name), ft_strdup(value));
		add_variable_to_the_list(env, var, EQUAL_SIGN_DETECTED);
		return ;
	}
	if (!var && ft_strcmp(name, "OLDPWD") == 0)
	{
		var = init_env_variable(ft_strdup(name), ft_strdup(value));
		add_variable_to_the_list(env, var, EQUAL_SIGN_DETECTED);
		return ;
	}
	if (!var)
		return ;
	change_env_var_value(var, value);
}

//change value
void	change_env_var_value(t_var *var, char *new_value)
{
	if (!new_value)
		return ;
	if (var->variable_value != NULL)
		free(var->variable_value);
	if (new_value)
		var->variable_value = ft_strdup(new_value);
}
