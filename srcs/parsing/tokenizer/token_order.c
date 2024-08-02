/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:20:27 by jewu              #+#    #+#             */
/*   Updated: 2024/08/02 15:12:29 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	convert_to_file(t_token *token)
{
	if ((token->token_type == TOKEN_OUTPUT || token->token_type == TOKEN_APPEND
			|| token->token_type == TOKEN_INPUT) && (token->next))
	token->next->token_type = TOKEN_FILE;
}
/* Change arg to file if we are in an redirection operator */

static int	input_heredoc_order(t_token *token)
{
	if (!token)
		return (FAILURE);
	if (token->token_type == TOKEN_INPUT)
	{
		if (token->previous)
		{
			if (token->previous->token_type != TOKEN_CMD
				&& token->previous->token_type != TOKEN_BUILTIN)
			{
				error("Command not valid\n");
				return (FAILURE);
			}
		}
	}
	if (token->token_type == TOKEN_INPUT || token->token_type == TOKEN_HEREDOC)
	{
		if (!token->next)
		{
			error("Syntax error\n");
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
			error("Missing outfile\n");
			return (FAILURE);
		}
		if (token->next->token_type != TOKEN_ARG
			&& token->next->token_type != TOKEN_BUILTIN)
		{
			error("Syntax error\n");
			return (FAILURE);
		}
	}
	convert_to_file(token);
	return (SUCCESS);
}
/* Change arg to file if we are in an redirection operator */

static int	first_cmd_redirection(t_token *token, int i)
{
	if (!token)
		return (FAILURE);
	if ((token->token_type != TOKEN_CMD
			&& token->token_type != TOKEN_BUILTIN
			&& token->token_type != TOKEN_INPUT
			&& token->token_type != TOKEN_HEREDOC
			&& token->token_type != TOKEN_OUTPUT
			&& token->token_type != TOKEN_APPEND
			&& token->token_type != TOKEN_VARIABLEASSIGNATION
			&& i == 0))
	{
		error("Check your 1st token\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
/* Check if 1st token is command or builtin */

int	token_order(t_env *envp, t_token *token)
{
	int	i;

	i = 0;
	(void)envp;
	if (!token)
		return (FAILURE);
	while (token)
	{
		if (first_cmd_redirection(token, i) == FAILURE)
			return (FAILURE);
		if ((output_append_order(token) == FAILURE)
			|| (input_heredoc_order(token) == FAILURE))
			return (FAILURE);
		if (token->token_type == TOKEN_PIPE
			&& token->next->token_type == TOKEN_PIPE)
		{
			error("syntax error near '|'\n");
			return (FAILURE);
		}
		token = token->next;
		i++;
	}
	return (SUCCESS);
}
/* Check token order */