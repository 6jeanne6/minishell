/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_i_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:10:17 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/20 14:48:56 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_path(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && s1[start] != '\0')
		start++;
	if (end > start && s1[end - 1] == '\n')
		end--;
	ptr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, &s1[start], end - start + 1);
	ptr[end - start] = '\0';
	return (ptr);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*double_array_to_one_array(char **path)
{
	int		total_length;
	int		i;
	char	*result;

	total_length = 0;
	i = 0;
	if (!path)
		return (NULL);
	while (path[i] != NULL)
	{
		total_length += ft_strlen(path[i]);
		i++;
	}
	result = (char *)malloc((total_length + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (path[i])
	{
		ft_strcat(result, path[i]);
		i++;
	}
	return (result);
}
