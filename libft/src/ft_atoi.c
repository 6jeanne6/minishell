/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:04:12 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:52:48 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

/*
ATOI = Ascii to Integer
Exemple : "   	-2652051"
i = pour se deplacer dans le tableau
result = pour stocker le resultat
sign = 1 pour determiner le signe de result en fonction du signe

1er while : si ya des espaces ou tab
if = determiner le signe du result
2eme while : calcul du result en int 
0 * 10 + 5 (ascii 53) - '0' (ascii 48)
*/