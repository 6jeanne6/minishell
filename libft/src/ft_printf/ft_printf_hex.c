/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:33:35 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:53:44 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_hex(unsigned long num, char base)
{
	int		len;
	char	*base_lower;
	char	*base_upper;

	len = 0;
	base_lower = "0123456789abcdef";
	base_upper = "0123456789ABCDEF";
	if (num >= 16)
	{
		len += ft_printf_hex(num / 16, base);
		len += ft_printf_hex(num % 16, base);
	}
	else if (num < 16 && base == 'x')
		len += ft_putchar(base_lower[num]);
	else if (num < 16 && base == 'X')
		len += ft_putchar(base_upper[num]);
	return (len);
}

/*
* ~~~ int	ft_printf_hex(unsigned long num, char base) ~~~
* Recursivity until num reaches < 16
* Base is used once num reaches < 16 to determine if it's lower or upper format
* Function returns length of the characters printed
*/

int	ft_printf_address(unsigned long address)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (!address)
	{
		ft_printf_putstr("(nil)");
		return (5);
	}
	count += ft_printf_putstr("0x");
	if (address < 16)
		count += ft_putchar(base[address]);
	else
	{
		count += ft_printf_hex(address / 16, 'x');
		count += ft_printf_hex(address % 16, 'x');
	}
	return (count);
}

/*
* ~~~ int	ft_printf_address(unsigned long address) ~~~
* Use hexadecimal lower format
* If address is NULL, sends (nil)
* Writes '0x'
* And then recursivity function to print hexadecimal format
* Function returns length of the characters printed
*/
