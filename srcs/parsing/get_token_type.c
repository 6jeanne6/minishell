/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:43:23 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/07/25 15:39:26 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *word)
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

static int is_redirection(char *word)
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


static int	check_file(char *word)
{
	int fd;

	fd = open(word, O_RDONLY);
    if (fd < 0) 
		return (FAILURE);
	return (SUCCESS);
}

static int	is_cmd(t_env *envp, t_token *token)
{
	if ((access(token->word, F_OK) == 0) 
		&& (access(token->word, X_OK) == 0))
		return (SUCCESS);
	if (check_path(envp, token) == SUCCESS)
		return (SUCCESS);
	return(FAILURE);
}


int get_token_type(t_env *envp, t_token *token)
{
	while (token)
	{
		if (token->outer_double_quote == 0 && token->outer_single_quote == 0)
		{
			if (is_redirection(token->word) >= 0)
				token->token_type = is_redirection(token->word);
			else if (is_variable_declaration(token->word) == SUCCESS)
				token->token_type = TOKEN_VARIABLEASSIGNATION;
			else if (check_file(token->word) == SUCCESS)
				token->token_type = TOKEN_FILE;
			else if (is_builtin(token->word) == SUCCESS)
				token->token_type = TOKEN_BUILTIN;
			else if (is_cmd(envp, token) == SUCCESS)
				token->token_type = TOKEN_CMD;
			else
				token->token_type = TOKEN_ARG;
		}
		else if (is_variable(token->word) == SUCCESS 
			&& token->outer_single_quote == 0)
			token->token_type = TOKEN_VARIABLE;
		else
			token->token_type = TOKEN_ARG;
		token = token->next;
	}
	return (SUCCESS);
}

