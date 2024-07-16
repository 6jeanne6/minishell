/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:43:15 by jewu              #+#    #+#             */
/*   Updated: 2024/07/16 22:53:43 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing_gear_5(t_shell *gear_5, t_env *envp)
{
	int	i;

	i = -1;
	(void)envp;
	if (!gear_5)
		error("Gear 5 is empty!\n");
	while (gear_5->input[++i])
	{
		if (gear_5->input[i] == '>' || gear_5->input[i] == '<')
		{
			if (check_redirection(gear_5->input) == FAILURE)
				return (FAILURE);
		}
		else if (gear_5->input[i] == '|')
		{
			if (check_pipe(gear_5->input) == FAILURE)
				return (FAILURE);
		}
		else if ((gear_5->input[i] == '\'') || (gear_5->input[i] == '"'))
		{
			if (check_quotes(gear_5->input) == FAILURE)
				return (FAILURE);
		}
		else if (check_special_characters(gear_5->input) == FAILURE)
			return (FAILURE);
		else if (gear_5->input[i] == '=')
		{
			if (check_variable(gear_5->input) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
//1st check lexical syntax for pre-parsing