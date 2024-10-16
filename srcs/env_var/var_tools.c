/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:37:05 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/14 19:15:38 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Copy and malloc a new string */
char	*malloc_strcpy(char *origin)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(origin) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (origin[i])
	{
		str[i] = origin[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

/* Malloc a sub-string of x length
to get a new variable into environment list */
char	*malloc_substr_and_cpy(const char *original_str, int start, int end)
{
	char	*new_str;
	int		len;
	int		i;

	i = 0;
	len = (end - start) + 1;
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[i] = original_str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/* Free all variable in environment */
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
