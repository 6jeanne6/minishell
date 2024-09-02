/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 11:49:40 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/02 16:49:48 by jewu             ###   ########.fr       */
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
			return (FAILURE);
		else if (input[i] == '|')
			return (SUCCESS);
		i++;
	}
	return (SUCCESS);
}
