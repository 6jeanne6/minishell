/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:18 by jewu              #+#    #+#             */
/*   Updated: 2024/09/23 11:51:07 by jewu             ###   ########.fr       */
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

/* Begin where are seperator characters and extract words */
void	extract_words(const char *line, t_token **head,
		t_env *envp, t_shell *gear_5)
{
	t_parsing	state;
	int			word_length;
	char		*linee;

	ft_bzero(&state, sizeof(t_parsing));
	linee = expander_test(envp, line, gear_5);
	word_length = ft_strlen(linee);
	state.current_word = ft_calloc(word_length + 1, sizeof(t_parsing));
	if (!state.current_word)
		return ;
	state.line = (char *)linee;
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
	free(linee);
	free(state.current_word);
}
