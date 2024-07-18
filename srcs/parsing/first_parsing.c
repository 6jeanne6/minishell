/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:43:15 by jewu              #+#    #+#             */
/*   Updated: 2024/07/15 16:53:30 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing_gear_5(t_shell *gear_5, t_env *envp)
{
	int	i;

	i = -1;
	if (!gear_5 || !envp)
		return (FAILURE);
	while (gear_5->input[++i])
	{
		if (gear_5->input[i] == '>' || gear_5->input[i] == '<')
		{
			if (is_redirection(gear_5->input) == SUCCESS)
				return (SUCCESS);
		}
		else if (gear_5->input[i] == '|')
		{
			if (is_pipe(gear_5->input) == SUCCESS)
				return (SUCCESS);
		}
	}
	return (FAILURE);
}
//1st check lexical syntax for pre-parsing