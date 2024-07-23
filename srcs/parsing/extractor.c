/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:18 by jewu              #+#    #+#             */
/*   Updated: 2024/07/23 17:55:56 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_words(const char *line, t_token **head)
{
	t_parsing	state;

	bzero(&state, sizeof(t_parsing));
	state.line = (char *)line;
	state.token_list = head;
	while (state.line[state.i] != '\0')
	{
		handle_characters(&state);
	}
	if (state.j > 0)
	{
		state.current_word[state.j] = '\0';
		add_to_list(state.token_list, state.current_word);
	}
}
