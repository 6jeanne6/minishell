/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:49:40 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/07/14 13:00:21 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (SUCCESS);
}
