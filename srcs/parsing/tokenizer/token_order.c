/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:20:27 by jewu              #+#    #+#             */
/*   Updated: 2024/09/02 17:14:37 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	filename_error(char *name, char *message, t_shell *gear_5, int flag)
{

	if (!message)
		return ;
	if (flag == 1)
	{
		error(name);
		error(": ");
		error(message);
		error("\n");
		gear_5->exit_status = 1;
	}
	else if (flag == 2)
	{
		error(message);
		error("\n");
		gear_5->exit_status = 2;
	}
}

static void	convert_to_file(t_token *token)
{
	if ((token->token_type == TOKEN_OUTPUT || token->token_type == TOKEN_APPEND
			|| token->token_type == TOKEN_INPUT) && (token->next))
	token->next->token_type = TOKEN_FILE;
}
/* Change arg to file if we are in an redirection operator */

static int	input_heredoc_order(t_token *token, t_shell *gear_5)
{
	if (!token || !gear_5)
		return (FAILURE);
	if (token->token_type == TOKEN_INPUT || token->token_type == TOKEN_HEREDOC)
	{
		if (token->previous)
		{
			if (token->previous->token_type != TOKEN_CMD
				&& token->previous->token_type != TOKEN_BUILTIN)
				return (FAILURE);
		}
		if (!token->next)
		{
			filename_error(token->word, "Error: insert a file", gear_5, 2);
			return (FAILURE);
		}
		if (is_file(token->next->word) == FAILURE)
		{
			filename_error(token->next->word, "inexistant file", gear_5, 1);
			return (FAILURE);
		}
	}
	convert_to_file(token);
	return (SUCCESS);
}
/* Change arg to file if we are in an redirection operator */

static int	output_append_order(t_token *token)
{
	if (!token)
		return (FAILURE);
	if ((token->token_type == TOKEN_OUTPUT
			|| token->token_type == TOKEN_APPEND))
	{
		if (!token->next)
		{
			return (FAILURE);
		}
		if (token->next->token_type != TOKEN_ARG
			&& token->next->token_type != TOKEN_BUILTIN
			&& token->next->token_type != TOKEN_CMD
			&& token->next->token_type != TOKEN_FILE)
		{
			return (FAILURE);
		}
	}
	convert_to_file(token);
	return (SUCCESS);
}
/* Change arg to file if we are in an redirection operator */

int	token_order(t_shell *gear_5, t_token *token)
{
	if (!token)
		return (FAILURE);
	while (token)
	{
		if ((output_append_order(token) == FAILURE)
			|| (input_heredoc_order(token, gear_5) == FAILURE))
		{
			return (FAILURE);
		}
		if (token->next)
		{
			if (token->token_type == TOKEN_PIPE
				&& token->next->token_type == TOKEN_PIPE)
			{
				return (FAILURE);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}
/* Check token order */