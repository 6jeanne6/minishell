/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:18 by jewu              #+#    #+#             */
/*   Updated: 2024/09/02 15:42:08 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_special_input(const char *line)
{
	while (*line != '\0')
	{
		if (line[0] == '\"' && line[1] == '\"')
			return (1);
		if (line[0] == '\'' && line[1] == '\'')
			return (1);
		line++;
	}
	return (0);
}

void	extract_words(const char *line, t_token **head)
{
	t_parsing	state;
	int			word_length;

	ft_bzero(&state, sizeof(t_parsing));
	word_length = ft_strlen(line);
	state.current_word = ft_calloc(word_length + 1, sizeof(t_parsing));
	if (!state.current_word)
		return ;
	state.line = (char *)line;
	state.token_list = head;
	while (state.line[state.i] != '\0')
		handle_characters(&state, word_length);
	if (state.j > 0)
	{
		state.current_word[state.j] = '\0';
		add_to_list(state.token_list, &state, state.current_word, word_length);
	}
	else if (state.j == 0 && check_special_input(line))
		add_to_list(state.token_list, &state, "", 0);
	free(state.current_word);
}
//begin where are seperator characters and extract words
