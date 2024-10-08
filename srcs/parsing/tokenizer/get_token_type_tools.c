/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:41:36 by jewu              #+#    #+#             */
/*   Updated: 2024/10/04 15:12:16 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check if token type is redirection
bool	token_is_a_redirection(t_token *token)
{
	if (!token)
		return (false);
	if (token->token_type == TOKEN_OUTPUT
		|| token->token_type == TOKEN_INPUT
		|| token->token_type == TOKEN_APPEND
		|| token->token_type == TOKEN_HEREDOC)
		return (true);
	return (false);
}

/* Check syntax of $environment variable */
int	is_variable(const char *input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == '\0')
		return (FAILURE);
	if (input[i] == '$')
		i++;
	else
		return (FAILURE);
	if (input[i] == '\0')
		return (FAILURE);
	while (input[i])
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/* Check syntax of variable assignant name=value or name= */
//name should begin with letter
int	is_variable_declaration(const char *input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == '\0')
		return (FAILURE);
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (FAILURE);
	if (input[i] == '_' && input[i + 1] == '=')
		return (FAILURE);
	while (input[i] != '\0' && input[i] != '=')
	{
		if (!ft_isalnum(input[i]))
		{
			if (input[i] != '_')
				return (FAILURE);
		}
		i++;
	}
	if (input[i] == '=')
		return (SUCCESS);
	return (FAILURE);
}
