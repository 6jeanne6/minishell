/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:35:21 by jewu              #+#    #+#             */
/*   Updated: 2024/08/07 14:20:21 by jewu             ###   ########.fr       */
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
			{
				error("'\\' is not interpreted!\n");
				return (FAILURE);
			}
			if (input[i] == ';')
			{
				error("';' is not interpreted!\n");
				return (FAILURE);
			}
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
		{
			error("Error: '||' is not interpreted!\n");
			return (FAILURE);
		}
		else if (input[i] == '|')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}
//check if only a single pipe
