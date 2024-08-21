/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:37:25 by jewu              #+#    #+#             */
/*   Updated: 2024/08/21 16:20:59 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(t_parsing *state, int word_length)
{
	if (state->j > 0)
	{
		state->current_word[state->j] = '\0';
		add_to_list(state->token_list, state, state->current_word, word_length);
		state->j = 0;
		state->outer_double_quote = 0;
		state->outer_single_quote = 0;
	}
}

//Blank = separator so we extract word
void	handle_special_char(t_parsing *state, int word_length)
{
	if (state->j > 0)
	{
		state->current_word[state->j] = '\0';
		add_to_list(state->token_list, state, state->current_word, word_length);
		state->j = 0;
		state->outer_double_quote = 0;
		state->outer_single_quote = 0;
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
	add_to_list(state->token_list, state, state->current_word, word_length);
}

//Copy special char such as > or >> or < or <<
void	process_token(t_parsing *state, int word_length)
{
	if (state->j > 0)
	{
		state->current_word[state->j] = '\0';
		add_to_list(state->token_list, state, state->current_word, word_length);
		state->j = 0;
		state->outer_double_quote = 0;
		state->outer_single_quote = 0;
	}
}
