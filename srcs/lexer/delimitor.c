/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:37:29 by jewu              #+#    #+#             */
/*   Updated: 2024/07/16 22:55:49 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool i_am_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}
//check if it's a quote ' or "
static bool pipe_character(char c)
{
	if (c == '|')
		return (true);
	return (false);
}
//check if it's pipe |

static bool	i_am_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
//check if it's space or tab

static bool	backslash_null(char c)
{
	if (c == '\0')
		return (true);
	return (false);
}
//check if we are in end of string \0

int	i_am_delimitor(char *str)
{
	int	i;

	i = -1;
	if (!str)
		error("Delimitor: no input\n");
	while (str[++i])
	{
		if ((i_am_blank(str[i]) == true)
			|| (backslash_null(str[i]) == true)
			|| (pipe_character(str[i]) == true)
			|| (i_am_quote(str[i]) == true)
			|| (str[i] == '<')
			|| (str[i] == '>'))
			return (SUCCESS);
	}
	return (FAILURE);
}
//the letter is a delimitor for bash
//		→ Blank = space, tab
//		→ Redirector < > >> <<
//		→ Backslash \0