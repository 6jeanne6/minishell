/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:43:15 by jewu              #+#    #+#             */
/*   Updated: 2024/07/18 14:02:03 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexing_again(char *input, char c, bool has_quotes)
{
	if ((c == '\'') || (c == '"'))
	{
		if (check_quotes(input) == FAILURE)
			return (FAILURE);
		has_quotes = true;
	}
	else if (check_special_characters(input) == FAILURE)
		return (FAILURE);
	else if (c == '=')
	{
		if (check_variable(input, has_quotes) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
//continuation of lexing_gear_5 function

int	lexing_gear_5(t_shell *gear_5)
{
	int		i;
	bool	has_quotes;

	i = -1;
	has_quotes = false;
	if (!gear_5)
		error("Gear 5 is empty!\n");
	while (gear_5->input[++i])
	{
		if (gear_5->input[i] == '>' || gear_5->input[i] == '<')
		{
			if (check_redirection(gear_5->input) == FAILURE)
				return (FAILURE);
		}
		else if (gear_5->input[i] == '|')
		{
			if (check_pipe(gear_5->input) == FAILURE)
				return (FAILURE);
		}
		else if (lexing_again(gear_5->input, gear_5->input[i], has_quotes)
			== FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
//1st check lexical syntax for pre-parsing