/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:36:56 by jewu              #+#    #+#             */
/*   Updated: 2024/07/14 22:08:30 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	i_am_delimitor(t_shell *gear_5, t_env *envp)
{
	int	i;

	i = -1;
	if (!gear_5 || !envp)
		return (FAILURE);
	while (gear_5->input[++i])
	{
		if ((i_am_blank(gear_5->input[i]) == true)
			|| (backslash_null(gear_5->input[i]) == true))
			break ;
	}
	return (FAILURE);
}
//the letter is a delimitor for bash
//		→ Blank = space, tab
//		→ Redirector < > >> <<
//		→ Backslash \0

int	lexing_gear_5(t_shell *gear_5, t_env *envp)
{
	if (!gear_5 || !envp)
		return (FAILURE);
	if (is_redirection(gear_5->input) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
//main lexing function to check lexical syntax