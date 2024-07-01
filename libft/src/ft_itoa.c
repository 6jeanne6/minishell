/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:56:33 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:52:39 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	size_t	count_characters(int n)
{
	size_t	count_n;

	count_n = 0;
	if (n == -2147483648)
		count_n = 11;
	else if (n < 0)
	{
		n *= -1;
		count_n = 1;
	}
	else if (n == 0)
		count_n = 1;
	while (n >= 1)
	{
		n = n / 10;
		count_n++;
	}
	return (count_n);
}

char	*ft_itoa(int n)
{
	int		i;
	int		is_negative;
	long	nb;
	char	*ptr;

	i = count_characters(n);
	nb = (long)n;
	is_negative = 0;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (0);
	if (nb < 0)
	{
		nb *= -1;
		ptr[0] = '-';
		is_negative = 1;
	}
	ptr[i] = '\0';
	while (i > is_negative)
	{
		ptr[i - 1] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (ptr);
}
/*
ITOA = Int to Ascii
Compter le nombre de caracteres dans un nombre, y compris le signe -
Prendre en compte si c'est positif ou negatif et INT MIN
Calculer avec n / 10

Malloc avec le count_characters
Gerer le cas negatif ou ptr[0] = '-'
Mettre \0 a la fin
Puis ecrire les chiffres jusqu'a is_negative en desiterant
en partant de la droite avec nb % 10 + '0'
Et on met nb = nb / 10 pour partir vers la gauche
*/