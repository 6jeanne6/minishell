/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:35:21 by jewu              #+#    #+#             */
/*   Updated: 2024/07/15 17:36:15 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				ft_putstr_fd("Error : ", STDERR_FILENO);
				ft_putstr_fd("'\' is not interpreted!\n", STDERR_FILENO);
				return (FAILURE);
			}
			if (input[i] == ';')
			{
				ft_putstr_fd("Error : ", STDERR_FILENO);
				ft_putstr_fd("';' is not interpreted!\n", STDERR_FILENO);
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}

int	is_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|' && input[i + 1] == '|')
		{
			ft_putstr_fd("Error :'||' is not interpreted!\n", STDERR_FILENO);
			return (FAILURE);
		}
		else if (input[i] == '|')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}
