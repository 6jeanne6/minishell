/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:35:21 by jewu              #+#    #+#             */
/*   Updated: 2024/09/02 16:49:56 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_special_char(char c)
{
	if (c == '>')
		return ('>');
	else if (c == '<')
		return ('<');
	else if (c == '&')
		return ('&');
	else if (c == '|')
		return ('|');
	else
		return ('\0');
}
// > or < or & or |

int	check_special_characters(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' || input[i] == ';')
		{
			if (input[i] == '\\')
				return (FAILURE);
			if (input[i] == ';')
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
//returns error if \ or ;

int	check_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|' && input[i + 1] == '|')
			return (FAILURE);
		else if (input[i] == '|')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}
//check if only a single pipe
