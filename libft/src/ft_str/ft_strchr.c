/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:42:41 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:51:32 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	j;

	j = 0;
	while (s[j] != '\0')
	{
		if (s[j] == (unsigned char)c)
			return ((char *) &s[j]);
		j++;
	}
	if (s[j] == (unsigned char)c)
		return ((char *) &s[j]);
	return (0);
}
