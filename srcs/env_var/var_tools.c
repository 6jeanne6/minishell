/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:37:05 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/07/17 18:01:27 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_substr_and_cpy(const char *original_str, int start, int end)
{
	char	*new_str;
	int		len;
	int		i;

	i = 0;
	len = (end - start) + 1;
	new_str = malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		new_str[i] = original_str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
void	free_var_list(t_env *env)
{
	t_var	*current_var;
	t_var	*next_var;

	current_var = env->first_variable;
	while (current_var != NULL)
	{
		next_var = current_var->next;
		free(current_var->variable_name);
		free(current_var->variable_value);
		free(current_var);
		current_var = next_var;
	}
	env->first_variable = NULL;
}