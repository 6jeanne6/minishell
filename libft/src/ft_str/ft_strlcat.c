/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:28:15 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:51:43 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;

	dest_len = 0;
	src_len = 0;
	while (dest_len < size && dst[dest_len] != '\0')
		dest_len++;
	while (src[src_len] != '\0')
		src_len++;
	i = 0;
	while (i < src_len && dest_len + i + 1 < size)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if (dest_len + i < size)
		dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
