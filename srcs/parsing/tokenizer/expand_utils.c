/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:30:16 by jewu              #+#    #+#             */
/*   Updated: 2024/08/09 20:33:17 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substitute_compute(t_env *envp, char *word)
{
	t_var	*current_var;
	int		length;

	current_var = envp->first_variable;
	length = 0;
	while (current_var)
	{
		if (ft_strcmp(word, current_var->variable_name) == 0)
		{
			length = ft_strlen(current_var->variable_value);
			break ;
		}
		current_var = current_var->next;
	}
	free(word);
	return (length);
}
//compute after substitution

void	variable_compute(char *word, int *i, int *j)
{
	(*i)++;
	*j = 0;
	while (word[*i + *j] && word[*i + *j] != ' ' && word[*i + *j] != '$')
		(*j)++;
}
//compute when we are in a variable

int	how_many_dollar(char *str)
{
	int	i;
	int	dollar;

	i = -1;
	dollar = 0;
	if (!str)
		return (FAILURE);
	while (str[++i])
	{
		if (str[i] == '$')
			dollar++;
	}
	return (dollar);
}
//in total how many $