/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:31:46 by jewu              #+#    #+#             */
/*   Updated: 2024/08/09 20:33:21 by jewu             ###   ########.fr       */
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
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i += 1;
			if (ft_isalpha(str[i]) || str[i] == '_')
			{
				found++;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
				if (found == dollar_count)
					return (SUCCESS);
			}
			else
				return (FAILURE);
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

void	expand_double_quotes(t_token *list, t_env *envp)
{
	int		total;
	t_token	*token;

	if (!list || !envp)
		return ;
	total = 0;
	token = list;
	while (token)
	{
		if (token->token_type == TOKEN_ARG && token->outer_double_quote == 1)
		{
			if (check_valid_name(token->word) == FAILURE)
				return ;
			total += compute_substitution(token->word, envp);
		}
		token = token->next;
	}
	printf("Total of characters: %d\n", total);
}
//imagine echo "test $USER $PATH"