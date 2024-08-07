/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:31 by jewu              #+#    #+#             */
/*   Updated: 2024/08/07 18:16:29 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variable_substitution(t_token *list, t_env *envp, char *word)
{
	t_var	*current_var;
	int		flag;

	flag = 0;
	current_var = envp->first_variable;
	while (current_var != NULL)
	{
		if (ft_strcmp(word, current_var->variable_name) == 0)
		{
			free(list->word);
			list->word = ft_strdup(current_var->variable_value);
			flag = 1;
			break ;
		}
		current_var = current_var->next;
	}
	if (flag == 0)
		empty_string(list);
	free(word);
}

static int	check_if_variable_exist_in_quotes(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1] || str[i + 1] == '_')))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	expand_double_quotes(t_token *list, t_env *envp)
{
	char	*joined_word;
	char	*tmp_word;
	char	**split_word;

	if (check_if_variable_exist_in_quotes(list->word) == FAILURE)
		return ;
	split_word = ft_split(list->word,"$"); // Allocation de mémoire
	if (!split_word)
		return ;
	tmp_word = variable_substitution(split_word[]);
	ft_st
}
// While (str[index])
// Parcourir la string jusqua ce qu'il croise un dollar
//Si il croise un dollar (vérifié si c'est correctement une variable)
//Si c'est une variable remplacée la variable par sa valeur puis renvoyée l'index de f
//