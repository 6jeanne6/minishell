/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:22:56 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/07/14 12:50:51 by lnjoh-tc         ###   ########.fr       */
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
