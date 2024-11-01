/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:52:41 by jewu              #+#    #+#             */
/*   Updated: 2024/10/20 14:49:44 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_double_quotes(t_parsing *state)
{
	if (state->in_double_quote)
	{
		if (state->j == 0)
			add_to_list(state->token_list, state, "", 0);
		state->in_double_quote = 0;
		state->outer_double_quote = 0;
	}
	else if (state->in_single_quote)
		state->current_word[state->j++] = state->line[state->i];
	else
	{
		if (!state->in_single_quote)
			state->outer_double_quote = 1;
		state->in_double_quote = 1;
	}
	state->i++;
}
// • Double quotes
// 		→ Ignore exterior quotes

static void	handle_single_quotes(t_parsing *state)
{
	if (state->in_single_quote)
	{
		if (state->j == 0)
			add_to_list(state->token_list, state, "", 0);
		state->in_single_quote = 0;
		state->outer_single_quote = 0;
	}
	else if (state->in_double_quote)
		state->current_word[state->j++] = state->line[state->i];
	else
	{
		if (!state->in_double_quote)
			state->outer_single_quote = 1;
		state->in_single_quote = 1;
	}
	state->i++;
}
// • Single quotes
// 		→ Ignore exterior quotes

void	handle_quotes(t_parsing *state)
{
	if (state->line[state->i] == '"')
		handle_double_quotes(state);
	else if (state->line[state->i] == '\'')
		handle_single_quotes(state);
}
//Quotes
// • Double quotes
// 		→ Ignore exterior quotes
// • Single quotes
// 		→ Ignore exterior quotes

void	handle_variable(t_parsing *state, int word_length)
{
	state->current_word[state->j++] = state->line[state->i++];
	while (state->line[state->i] != '\0'
		&& (ft_ispace(state->line[state->i]) == FAILURE)
		&& !is_special_char(state->line[state->i]))
	{
		if (state->line[state->i] == '"')
			handle_double_quotes(state);
		else if (state->line[state->i] == '\'')
			handle_single_quotes(state);
		else
			state->current_word[state->j++] = state->line[state->i++];
	}
	if (ft_ispace(state->line[state->i]) != FAILURE)
	{
		process_token(state, word_length);
		state->i++;
	}
	if (state->line[state->i] == '\0')
		process_token(state, word_length);
}

void	handle_characters(t_parsing *state, int word_length)
{
	if (state->line[state->i] == '\"' || state->line[state->i] == '\'')
		handle_quotes(state);
	else if ((ft_ispace(state->line[state->i]) == SUCCESS)
		&& (!state->in_double_quote) && (!state->in_single_quote))
	{
		handle_space(state, word_length);
		state->i++;
	}
	else if (is_special_char(state->line[state->i])
		&& !state->in_double_quote && !state->in_single_quote)
		handle_special_char(state, word_length);
	else if (state->line[state->i] == '$'
		&& !state->in_double_quote && !state->in_single_quote)
		handle_variable(state, word_length);
	else
		state->current_word[state->j++] = state->line[state->i++];
}
//Buffer copies letters until we are in a separator
//Reinitialize j to 0 and redo same procedure
