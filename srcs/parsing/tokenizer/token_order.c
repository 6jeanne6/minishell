/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:20:27 by jewu              #+#    #+#             */
/*   Updated: 2024/08/02 19:21:51 by jewu             ###   ########.fr       */
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

static int	input_heredoc_order(t_shell *gear_5, t_token *token)
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
				error("Command not found\n");
				return (gear_5->exit_status = 127, FAILURE);
			}
		}
	}
	if (token->token_type == TOKEN_INPUT || token->token_type == TOKEN_HEREDOC)
	{
		if (!token->next)
		{
			error("Syntax error\n");
			return (gear_5->exit_status = 2, FAILURE);
		}
	}
	convert_to_file(token);
	return (SUCCESS);
}
/* Change arg to file if we are in an redirection operator */

static int	output_append_order(t_shell *gear_5, t_token *token)
{
	if (!token || !gear_5)
		return (FAILURE);
	if ((token->token_type == TOKEN_OUTPUT
			|| token->token_type == TOKEN_APPEND))
	{
		if (!token->next)
		{
			error("Missing outfile\n");
			return (gear_5->exit_status = 2, FAILURE);
		}
		if (token->next->token_type != TOKEN_ARG
			&& token->next->token_type != TOKEN_BUILTIN
			&& token->next->token_type != TOKEN_CMD)
		{
			error("Syntax error\n");
			return (gear_5->exit_status = 2, FAILURE);
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
	if ((token->token_type != TOKEN_BUILTIN
			&& token->token_type != TOKEN_INPUT
			&& token->token_type != TOKEN_HEREDOC
			&& token->token_type != TOKEN_OUTPUT
			&& token->token_type != TOKEN_APPEND
			&& token->token_type != TOKEN_VARIABLEASSIGNATION
			&& token->token_type != TOKEN_CMD
			&& i == 0))
	{
		error("Check your 1st token\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
/* Check if 1st token is command or builtin */

int	token_order(t_env *envp, t_token *token, t_shell *gear_5)
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
		if ((output_append_order(gear_5, token) == FAILURE)
			|| (input_heredoc_order(gear_5, token) == FAILURE))
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