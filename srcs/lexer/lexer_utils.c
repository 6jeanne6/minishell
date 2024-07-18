/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:35:21 by jewu              #+#    #+#             */
/*   Updated: 2024/07/18 14:01:19 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_variable(char *input, bool has_quotes)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '=')
		{
			if (has_quotes == false)
			{
				if (input[i - 1] == ' ' || input[i + 1] == ' ')
				{
					error("Check your = again\n");
					return (FAILURE);
				}
			}
		}
	}
	return (SUCCESS);
}
//if =, checks if there is no space before and after

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
