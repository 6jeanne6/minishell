/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:57:12 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:54:04 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_putstr(const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str != NULL)
	{
		while (str[i] != '\0')
		{
			len += ft_putchar(str[i]);
			i++;
		}
	}
	else
		len += ft_printf_putstr("(null)");
	return (len);
}
