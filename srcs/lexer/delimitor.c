/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:37:29 by jewu              #+#    #+#             */
/*   Updated: 2024/10/17 16:45:43 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	pipe_character(char c)
{
	if (c == '|')
		return (true);
	return (false);
}
//check if it's pipe |

int	ft_ispace(char c)
{
	if ((c == '\t') || (c == '\n') || (c == '\v') || (c == '\f')
		|| (c == ' '))
		return (SUCCESS);
	return (FAILURE);
}

static bool	backslash_null(char c)
{
	if (c == '\0')
		return (true);
	return (false);
}
//check if we are in end of string \0

int	i_am_delimitor(char c)
{
	if (!c)
		error("Delimitor: no character\n");
	if ((backslash_null(c) == true)
		//|| (i_am_blank(c) == true)
		|| (pipe_character(c) == true)
		// || (i_am_quote(c) == true)
		|| (c == '<')
		|| (c == '>'))
		return (SUCCESS);
	return (FAILURE);
}
//the letter is a delimitor for bash
//		→ Blank = space, tab
//		→ Redirector < > >> <<
//		→ Backslash \0