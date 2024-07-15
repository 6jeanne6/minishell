/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimitor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:37:29 by jewu              #+#    #+#             */
/*   Updated: 2024/07/15 19:28:57 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	i_am_delimitor(char *str, t_env *envp)
{
	int	i;

	i = -1;
	if (!str || !envp)
		error("Delimitor: no input or envp\n", envp);
	while (str[++i])
	{
		if ((i_am_blank(str[i]) == true)
			|| (backslash_null(str[i]) == true))
			return (SUCCESS);
	}
	return (FAILURE);
}
//the letter is a delimitor for bash
//		→ Blank = space, tab
//		→ Redirector < > >> <<
//		→ Backslash \0