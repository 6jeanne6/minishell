/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:43:15 by jewu              #+#    #+#             */
/*   Updated: 2024/10/21 16:47:43 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quotes(t_quotes *quotes, char c)
{
	if (c == '"')
		handle_double_quote(quotes);
	else if (c == '\'')
		handle_single_quote(quotes);
}

//check if no >>> or <<< or <> or >< and no ||
static int	check_special_chars(t_shell *gear_5, int i, t_quotes *quotes)
{
	if (quotes->inside_single_quotes == 0 && quotes->inside_double_quotes == 0)
	{
		if (gear_5->input[i] == '>' || gear_5->input[i] == '<')
		{
			if (check_redirection(gear_5->input) == FAILURE)
			{
				update_exit_status(gear_5, 2, NULL);
				return (FAILURE);
			}
		}
		else if (gear_5->input[i] == '|')
		{
			if (check_pipe(gear_5->input) == FAILURE)
			{
				update_exit_status(gear_5, 2, NULL);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

//check amount of quotes and if there is no \ or ;
static int	lexing_again(char *input, char c, bool *has_quotes, t_shell *gear_5)
{
	if (c == '\'' || c == '"')
	{
		if (check_quotes(input) == FAILURE)
		{
			update_exit_status(gear_5, 2, NULL);
			return (FAILURE);
		}
		*has_quotes = true;
	}
	else if (check_special_characters(input) == FAILURE)
	{
		update_exit_status(gear_5, 2, NULL);
		return (FAILURE);
	}
	return (SUCCESS);
}

//check lexing
int	lexing_gear_5(t_shell *gear_5)
{
	int			i;
	bool		has_quotes;
	t_quotes	quotes;

	i = -1;
	quotes.inside_single_quotes = 0;
	quotes.inside_double_quotes = 0;
	has_quotes = false;
	if (!gear_5)
	{
		update_exit_status(NULL, 1, NULL);
		return (FAILURE);
	}
	while (gear_5->input[++i])
	{
		if (gear_5->input[i] == '\"' || gear_5->input[i] == '\'')
			update_quotes(&quotes, gear_5->input[i]);
		if (check_special_chars(gear_5, i, &quotes) == FAILURE)
			return (FAILURE);
		if (lexing_again(gear_5->input, gear_5->input[i],
				&has_quotes, gear_5) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
