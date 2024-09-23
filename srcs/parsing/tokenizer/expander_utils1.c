/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:31:46 by jewu              #+#    #+#             */
/*   Updated: 2024/09/23 12:07:15 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increment_i_k(int *i, int *k)
{
	(*i)++;
	(*k)++;
}

//increment i and k LOL
static int	compute_substitution(char *word, t_env *envp)
{
	int		i;
	int		j;
	int		k;
	int		total;
	char	*tmp;

	i = 0;
	k = 0;
	total = 0;
	if (!word)
		return (FAILURE);
	while (word[i])
	{
		if (word[i] == '$')
		{
			j = 0;
			variable_compute(word, &i, &j);
			tmp = ft_substr(word, i, j);
			total += substitute_compute(envp, tmp);
			i += j;
		}
		else
			increment_i_k(&i, &k);
	}
	return (total + k);
}

//compute how many alloc needed after subsitution of $
static int	syntax_variable(char *str, int dollar_count)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	if (!str)
		return (FAILURE);
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i += 1;
			if (ft_isalpha(str[i]) || str[i] == '_')
			{
				found++;
				i++;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
				if (found == dollar_count)
					return (SUCCESS);
				i--;
			}
		}
	}
	return (FAILURE);
}
//while loop to check $syntax

static int	check_valid_name(char *str)
{
	int	dollar_count;

	if (!str)
		return (FAILURE);
	dollar_count = how_many_dollar(str);
	if (syntax_variable(str, dollar_count) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
//check syntax of variable name, must be a letter after $

void	expand_content(t_token *list, t_env *envp)
{
	int		total;
	t_token	*token;
	char	*expanded_content;

	if (!list || !envp)
		return ;
	total = 0;
	token = list;
	while (token)
	{
		if (check_valid_name(token->word) == FAILURE)
			return ;
		total += compute_substitution(token->word, envp);
		token = token->next;
	}
	expanded_content = create_new_word(list, envp, total);
	free(list->word);
	list->word = expanded_content;
}
//imagine echo "test $USER $PATH"