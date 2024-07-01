/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:27:47 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:54:00 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static long	ft_count_characters(long n)
{
	size_t	count_n;

	count_n = 0;
	if (n < 0)
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
/*
count_characters to count the number of characters in a number
long = only in 32-bits architecture
long = from -2 147 463 647 to 2 147 483 647 
*/

static void	ft_putnbr(long nb)
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

int	ft_printf_itoa(int n)
{
	long	nb;
	int		size;

	nb = n;
	size = 0;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
		size = 1;
	}
	size += ft_count_characters(nb);
	ft_putnbr(nb);
	return (size);
}
