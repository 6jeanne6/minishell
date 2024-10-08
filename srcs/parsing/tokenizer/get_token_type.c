/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:43:23 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/04 15:09:54 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check if it's a BUILTIN */
int	is_builtin(char *word)
{
	if (ft_strcmp(word, "echo") == 0)
		return (SUCCESS);
	if (ft_strcmp(word, "cd") == 0)
		return (SUCCESS);
	if (ft_strcmp(word, "pwd") == 0)
		return (SUCCESS);
	if (ft_strcmp(word, "env") == 0)
		return (SUCCESS);
	if (ft_strcmp(word, "export") == 0)
		return (SUCCESS);
	if (ft_strcmp(word, "unset") == 0)
		return (SUCCESS);
	if (ft_strcmp(word, "exit") == 0)
		return (SUCCESS);
	return (FAILURE);
}

/* check if it's a redirection operator */
static int	is_redirection(char *word)
{
	if (ft_strcmp(word, "|") == SUCCESS)
		return (TOKEN_PIPE);
	if (ft_strcmp(word, ">>") == SUCCESS)
		return (TOKEN_APPEND);
	if (ft_strcmp(word, "<<") == SUCCESS)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(word, "<") == SUCCESS)
		return (TOKEN_INPUT);
	if (ft_strcmp(word, ">") == SUCCESS)
		return (TOKEN_OUTPUT);
	return (FAILURE);
}

/* Check if it's a binary or an executable */
static int	is_cmd(t_env *envp, t_token *token)
{
	if (token->word[0] == '/')
	{
		token->cmd_path = ft_strdup(token->word);
		return (SUCCESS);
	}
	if ((access(token->word, F_OK) == 0)
		&& (access(token->word, X_OK) == 0))
		return (SUCCESS);
	if (check_path(envp, token) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

/* Determine token type*/
static int	determine_token_type(t_env *envp, t_token *token)
{
	if (is_redirection(token->word) >= 0)
		return (is_redirection(token->word));
	else if (is_variable_declaration(token->word) == SUCCESS)
		return (TOKEN_VARIABLEASSIGNATION);
	else if (is_variable(token->word) == SUCCESS)
		return (TOKEN_VARIABLE);
	else if (is_builtin(token->word) == SUCCESS)
		return (TOKEN_BUILTIN);
	else if (is_cmd(envp, token) == SUCCESS)
		return (TOKEN_CMD);
	else
		return (TOKEN_ARG);
}

/* classify extracted word into a TOKEN type */
int	get_token_type(t_env *envp, t_token *token)
{
	while (token)
	{
		if (token->outer_double_quote == 0 && token->outer_single_quote == 0)
			token->token_type = determine_token_type(envp, token);
		else if ((is_variable_declaration(token->word) == SUCCESS)
			&& (token->outer_double_quote == 1
				|| token->outer_single_quote == 1))
			token->token_type = determine_token_type(envp, token);
		else if (is_variable(token->word) == SUCCESS
			&& token->outer_double_quote == 1)
			token->token_type = TOKEN_VARIABLE;
		else
			token->token_type = TOKEN_ARG;
		if (token_is_a_redirection(token) == true)
		{
			if (token->next)
			{
				token->next->token_type = TOKEN_FILE;
				token = token->next;
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}
