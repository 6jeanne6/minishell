/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uitoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:27:47 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:54:07 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	ft_count_characters(unsigned int n)
{
	int	count_n;

	count_n = 0;
	if (n == 0)
		count_n = 1;
	while (n >= 1)
	{
		n = n / 10;
		count_n++;
	}
	return (count_n);
}
/*
count_characters to count the number of characters in a number
*/

static void	ft_putnbr(unsigned int nb)
{
	if (nb >= 0 && nb < 10)
		ft_putchar(nb + '0');
	else if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}
/*
Permet d'ecrire un nombre en sortie.
Fait appel a la recursivite.
On fait en sorte de decouper le nombre jusqu'a ce qu'il soit entre 0 et 9.
Puis on fait ft_putchar(nb + '0').
*/

int	ft_printf_uitoa(unsigned int n)
{
	int	size;

	size = 0;
	size += ft_count_characters(n);
	ft_putnbr(n);
	return (size);
}
