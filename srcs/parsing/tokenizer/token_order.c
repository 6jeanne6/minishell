/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:20:27 by jewu              #+#    #+#             */
/*   Updated: 2024/10/28 16:48:48 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//verifications for heredoc
static int	heredoc_order(t_token *token, t_shell *gear_5)
{
	if (!token || !gear_5)
		return (FAILURE);
	if (token->token_type == TOKEN_HEREDOC)
	{
		if (!token->next)
		{
			filename_error(token->word, "Error: missing delimiter", gear_5, 2);
			return (FAILURE);
		}
		if (token->next && token->next->token_type == TOKEN_PIPE)
		{
			update_exit_status(gear_5, 2, NULL);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

/* Change arg to file if we are in an redirection operator */
static void	convert_to_file(t_token *token)
{
	if ((token->token_type == TOKEN_OUTPUT || token->token_type == TOKEN_APPEND
			|| token->token_type == TOKEN_INPUT) && (token->next))
	{
		if (token->next)
		{
			if (token->next->token_type != TOKEN_PIPE)
				token->next->token_type = TOKEN_FILE;
		}
	}
}

/* Change arg to file if we are in an redirection operator */
static int	input_order(t_token *token, t_shell *gear_5)
{
	if (token->token_type == TOKEN_INPUT)
	{
		if ((!token->next) && (token->outer_double_quote == 0
			&& token->outer_single_quote == 0))
		{
			filename_error(token->word, "Error: insert a file", gear_5, 2);
			return (FAILURE);
		}
		if (token->next)
		{
			if (token->next->token_type == TOKEN_PIPE)
			{
				update_exit_status(gear_5, 2, NULL);
				return (FAILURE);
			}
		}
	}
	convert_to_file(token);
	return (SUCCESS);
}

/* Change arg to file if we are in an redirection operator */
static int	output_append_order(t_token *token, t_shell *gear_5)
{
	if (!token || !gear_5)
		return (FAILURE);
	if ((token->token_type == TOKEN_OUTPUT
			|| token->token_type == TOKEN_APPEND))
	{
		if ((!token->next) && (token->outer_double_quote == 0
			|| token->outer_single_quote == 0))
			return (FAILURE);
		if (token->next)
		{
			if (token->next->token_type == TOKEN_PIPE)
				return (FAILURE);
			if (token->next->token_type != TOKEN_ARG
				&& token->next->token_type != TOKEN_BUILTIN
				&& token->next->token_type != TOKEN_CMD
				&& token->next->token_type != TOKEN_FILE)
				return (FAILURE);
		}
	}
	convert_to_file(token);
	return (SUCCESS);
}

/* Check token order */
int	token_order(t_shell *gear_5, t_token *token)
{
	if (!token || !gear_5)
		return (FAILURE);
	while (token)
	{
		if ((output_append_order(token, gear_5) == FAILURE)
			|| (input_order(token, gear_5) == FAILURE)
			|| (heredoc_order(token, gear_5) == FAILURE)
			|| (pipe_order(token, gear_5) == FAILURE))
			return (FAILURE);
		if (token->previous)
		{
			if (token->token_type == TOKEN_CMD
				&& token->previous->token_type == TOKEN_CMD)
				token->token_type = TOKEN_ARG;
		}
		token = token->next;
	}
	return (SUCCESS);
}
