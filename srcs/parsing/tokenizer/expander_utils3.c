/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:50:35 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/14 15:49:18 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_word(t_env *env, t_shell *gear_5, t_token *token)
{
	const char	*var_value;

	var_value = expander_test(env, token->word, gear_5);
	if (var_value)
	{
		free(token->word);
		token->word = (char *)var_value;
	}
}

static int	here_doc_detected(t_token *list)
{
	t_token	*start;

	start = list;
	while (start != NULL)
	{
		if (start->token_type == TOKEN_HEREDOC)
			return (1);
		start = start->next;
	}
	return (0);
}

void	expander_two(t_env *env, t_shell *gear_5, t_token **list)
{
	t_token	*start;
	t_token	*prev;

	start = *list;
	prev = NULL;
	if (here_doc_detected(start) == 1)
	{
		while (start != NULL)
		{
			if (start->token_type == TOKEN_VARIABLE
				&& is_variable(start->word) == SUCCESS)
			{
				if (!start->outer_single_quote
					&& (prev == NULL || prev->token_type != TOKEN_HEREDOC))
					expand_word(env, gear_5, start);
			}
			prev = start;
			start = start->next;
		}
	}
	return ;
}
