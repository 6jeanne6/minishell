/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:33:10 by jewu              #+#    #+#             */
/*   Updated: 2024/07/16 22:55:11 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pair(int number)
{
	if (number % 2 == 0)
		return (SUCCESS);
	return (FAILURE);
}

static void	handle_single_quote(t_quotes *quotes)
{
	if (quotes->inside_double_quotes == 0)
	{
		quotes->nbofsingle++;
		if (quotes->inside_single_quotes == 0)
			quotes->inside_single_quotes = 1;
		else
			quotes->inside_single_quotes = 0;
	}
}

static void	handle_double_quote(t_quotes *quotes)
{
	if (quotes->inside_single_quotes == 0)
	{
		quotes->nbofdouble++;
		if (quotes->inside_double_quotes == 0)
			quotes->inside_double_quotes = 1;
		else
			quotes->inside_double_quotes = 0;
	}
}

static void	count_quotes(char *input, int *nbofsingle, int *nbofdouble)
{
	int			i;
	t_quotes	quotes;

	i = 0;
	quotes.nbofsingle = 0;
	quotes.nbofdouble = 0;
	quotes.inside_double_quotes = 0;
	quotes.inside_single_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			handle_single_quote(&quotes);
		else if (input[i] == '"')
			handle_double_quote(&quotes);
		i++;
	}
	*nbofsingle = quotes.nbofsingle;
	*nbofdouble = quotes.nbofdouble;
}

int	check_quotes(char *input)
{
	int	nbofsingle;
	int	nbofdouble;

	nbofsingle = 0;
	nbofdouble = 0;
	count_quotes(input, &nbofsingle, &nbofdouble);
	if (is_pair(nbofdouble) == FAILURE || is_pair(nbofsingle) == FAILURE)
	{
		error("Error : Quotes are not close!\n");
		return (FAILURE);
	}
	else
		return (SUCCESS);
}
