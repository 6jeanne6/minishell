/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:35:21 by jewu              #+#    #+#             */
/*   Updated: 2024/10/25 11:59:10 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_special_char(char c)
{
	if (c == '>')
		return ('>');
	else if (c == '<')
		return ('<');
	else if (c == '|')
		return ('|');
	else
		return ('\0');
}
// > or < or & or |

//returns error if \ or ;
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

//check if only a single pipe |
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
