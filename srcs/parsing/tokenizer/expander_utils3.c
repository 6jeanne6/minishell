/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:33:49 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/05 14:22:00 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_list(t_env *envp, char *variable)
{
	t_var	*begin_list;

	begin_list = envp->first_variable;
	while (begin_list != NULL)
	{
		if (ft_strcmp(variable, begin_list->variable_name) == 0)
			return (SUCCESS);
		begin_list = begin_list->next;
	}
	return (FAILURE);
}

int	get_var_value(t_env *envp, char *variable, char *new_word, int j)
{
	t_var	*begin_list;
	int		i;

	begin_list = envp->first_variable;
	i = 0;
	while (begin_list != NULL)
	{
		if (ft_strcmp(variable, begin_list->variable_name) == 0)
		{
			while (begin_list->variable_value[i])
				new_word[j++] = begin_list->variable_value[i++];
			break ;
		}
		begin_list = begin_list->next;
	}
	return (j);
}

int	treatment(char *word, t_env *envp, char *new_word, int j)
{
	int		i;
	int		start;
	char	*variable;

	i = 1;
	start = i;
	while (word[i] && word[i] != ' ' && word[i] != '"' && word[i] != '$')
		i++;
	variable = ft_strndup(&word[start], i - start);
	if (!variable)
		return (j);
	if (is_in_list(envp, variable) == 0)
		j = get_var_value(envp, variable, new_word, j);
	free(variable);
	return (j);
}

char	*create_new_word(t_token *list, t_env *envp, int len)
{
	int		i;
	int		j;
	char	*new_word;

	i = 0;
	j = 0;
	new_word = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_word)
		return (NULL);
	while (list->word[i] != '\0')
	{
		if (list->word[i] == '$')
		{
			j = treatment(&list->word[i], envp, new_word, j);
			while (list->word[i] && list->word[i] != ' '
				&& list->word[i] != '"')
			{
				if (list->word[i++] == '$')
					break ;
			}
		}
		else
			new_word[j++] = list->word[i++];
	}
	new_word[j] = '\0';
	return (new_word);
}
