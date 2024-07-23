/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:52:41 by jewu              #+#    #+#             */
/*   Updated: 2024/07/23 17:54:58 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(t_parsing *state)
{
	if (state->line[state->i] == '"')
	{
		if (state->in_double_quote)
			state->in_double_quote = 0;
		else if (state->in_single_quote)
			state->current_word[state->j++] = state->line[state->i];
		else
			state->in_double_quote = 1;
		state->i++;
	}
	else if (state->line[state->i] == '\'')
	{
		if (state->in_single_quote)
			state->in_single_quote = 0;
		else if (state->in_double_quote)
			state->current_word[state->j++] = state->line[state->i];
		else
			state->in_single_quote = 1;
		state->i++;
	}
}

void	handle_space(t_parsing *state)
{
	if (state->j > 0)
	{
		state->current_word[state->j] = '\0';
		add_to_list(state->token_list, state->current_word);
		state->j = 0;
	}
}

void	handle_special_char(t_parsing *state)
{
	if (state->j > 0)
	{
		state->current_word[state->j] = '\0';
		add_to_list(state->token_list, state->current_word);
		state->j = 0;
	}
	if ((state->line[state->i] == '>' && state->line[state->i + 1] == '>')
		|| (state->line[state->i] == '<' && state->line[state->i + 1] == '<'))
	{
		state->current_word[0] = state->line[state->i];
		state->current_word[1] = state->line[state->i + 1];
		state->current_word[2] = '\0';
		state->i += 2;
	}
	else
	{
		state->current_word[0] = state->line[state->i];
		state->current_word[1] = '\0';
		state->i++;
	}
	add_to_list(state->token_list, state->current_word);
}

void	handle_variable(t_parsing *state)
{
	if (state->j > 0)
	{
		state->current_word[state->j] = '\0';
		add_to_list(state->token_list, state->current_word);
		state->j = 0;
	}
	state->current_word[state->j++] = state->line[state->i++];
	while (!isspace(state->line[state->i])
		&& state->line[state->i] != '\0'
		&& !is_special_char(state->line[state->i]))
	{
		state->current_word[state->j++] = state->line[state->i++];
	}
	state->current_word[state->j] = '\0';
	add_to_list(state->token_list, state->current_word);
	state->j = 0;
}

void	handle_characters(t_parsing *state)
{
	if (state->line[state->i] == '\"' || state->line[state->i] == '\'')
	{
		handle_quotes(state);
	}
	else if (isspace(state->line[state->i])
		&& !state->in_double_quote && !state->in_single_quote)
	{
		handle_space(state);
		state->i++;
	}
	else if (is_special_char(state->line[state->i])
		&& !state->in_double_quote && !state->in_single_quote)
	{
		handle_special_char(state);
	}
	else if (state->line[state->i] == '$'
		&& !state->in_double_quote && !state->in_single_quote)
	{
		handle_variable(state);
	}
	else
	{
		state->current_word[state->j++] = state->line[state->i++];
	}
}
