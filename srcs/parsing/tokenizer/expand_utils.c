/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:30:16 by jewu              #+#    #+#             */
/*   Updated: 2024/08/09 15:31:03 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_dollar(char *str)
{
	int	i;
	int	dollar;

	i = -1;
	dollar = 0;
	if (!str)
		return (FAILURE);
	while (str[++i])
	{
		if (str[i] == '$')
			dollar++;
	}
	return (dollar);
}
//in total how many $