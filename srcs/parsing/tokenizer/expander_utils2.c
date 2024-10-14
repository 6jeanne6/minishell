/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:28:35 by jewu              #+#    #+#             */
/*   Updated: 2024/10/14 15:43:49 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check is is a valid character */
int	is_valid_character(char c, t_expand *xpd)
{
	if ((c == '"' || c == '\'') && !xpd->inside_double_quotes)
		return (FAILURE);
	if (ft_isdigit(c))
		return (FAILURE);
	return (SUCCESS);
}

/* Check if is a space or not*/
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

/* Copy a string */
char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	find_double_angle_brackets(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}
