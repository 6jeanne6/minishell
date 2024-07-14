/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:36:56 by jewu              #+#    #+#             */
/*   Updated: 2024/07/14 14:20:45 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexing_gear_5(t_shell *gear_5, t_env *envp)
{
	if (!gear_5 || !envp)
		return (FAILURE);
	if (is_redirection(gear_5->input) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}
//main lexing function to check lexical syntax