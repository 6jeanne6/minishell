/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:31 by jewu              #+#    #+#             */
/*   Updated: 2024/08/08 20:03:41 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	substitute_after(t_token *list, t_env *envp, char *word)
{
	t_var	*current_var;
	int		flag;
	int		length;

	flag = 0;
	current_var = envp->first_variable;
	length = 0;
	while (current_var)
	{
		if (ft_strcmp(word, current_var->variable_name) == 0)
		{
			free(list->word);
			list->word = ft_strdup(current_var->variable_value);
			flag = 1;
			length = ft_strlen(current_var->variable_value);
			break ;
		}
		current_var = current_var->next;
	}
	if (flag == 0)
		empty_string(list);
	if (flag == 0)
		length = 0;
	free(word);
	return (length);
}
//compute after substitution

static int	compute_substitution(t_token *list, char *word, t_env *envp)
{
	int		i;
	int		j;
	int		total;
	char	*tmp;

	i = -1;
	total = 0;
	tmp = NULL;
	if (!word)
		return (FAILURE);
	while (word[++i])
	{
		j = 0;
		if (word[i] == '$')
		{
			i++;
			j++;
			while (word[i] != ' ' || word[i] != '$')
				tmp[j++] = word[i++];
			total += substitute_after(list, envp, tmp);
			free(tmp);
		}
	}
	return (total);
}
//compute how many alloc needed after subsitution of $

static int how_many_dollar(char *str)
{
	int	i;
	int dollar;

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
//in total how mnany $

static int	check_valid_name(char *str)
{
	int	i;
	int	dollar;
	int found;

	i = -1;
	dollar = 0;
	found = 0;
	if (!str)
		return (FAILURE);
	dollar = how_many_dollar(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1] || str[i + 1] == '_')))
		{
			i += 1;
			found++;
			if (found == dollar)
				return (SUCCESS);
		}
	}
	return (FAILURE);
}
//check syntax of variable name, must be a letter after $

void	expand_double_quotes(t_token *list, t_env *envp)
{
	int		total;
	t_token *token;

	if (!list || !envp)
		return ;
	total = 0;
	token = list;
	while (token)
	{
		if (token->token_type == TOKEN_APPEND && token->outer_double_quote == 1)
		{
			if (check_valid_name(list->word) == FAILURE)
				return ;
			total = compute_substitution(list, list->word, envp);	
		}
		token = token->next;
	}
	printf("Total of characters: %d\n", total);
}
// While (str[index])
// Parcourir la string jusqua ce qu'il croise un dollar
//Si il croise un dollar (vérifié si c'est correctement une variable)
//Si c'est une variable remplacée la variable par sa valeur puis renvoyée l'index de f
//