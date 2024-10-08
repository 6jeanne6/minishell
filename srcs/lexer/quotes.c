/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:33:10 by jewu              #+#    #+#             */
/*   Updated: 2024/10/04 12:43:53 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if even number of quotes then SUCCESS
static int	is_pair(int number)
{
	if (number % 2 == 0)
		return (SUCCESS);
	return (FAILURE);
}

//check amount of single quotes when not inside double quotes
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

//check amount of double quotes when not inside single quotes
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

//use of t_quotes structure
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

//check amount of single or double quotes
//if quotes not close then ERROR
int	check_quotes(char *input)
{
	int	nbofsingle;
	int	nbofdouble;

	nbofsingle = 0;
	nbofdouble = 0;
	count_quotes(input, &nbofsingle, &nbofdouble);
	if (is_pair(nbofdouble) == FAILURE || is_pair(nbofsingle) == FAILURE)
		return (FAILURE);
	else
		return (SUCCESS);
}
