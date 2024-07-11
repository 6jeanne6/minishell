/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:22:56 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/07/11 12:30:36 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_characters(t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->input[i])
	{
		if (minishell->input[i] == '\\' || minishell->input[i] == ';')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

