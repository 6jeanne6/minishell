/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:38:10 by jewu              #+#    #+#             */
/*   Updated: 2024/05/30 16:50:46 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	count_words(char const *str, char c)
{
	size_t	i;
	size_t	bit;
	size_t	word;

	i = 0;
	bit = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c) && (bit == 0))
		{
			bit = 1;
			word++;
		}
		else if ((str[i] == c) && (bit == 1))
			bit = 0;
		i++;
	}
	return (word);
}

static	void	free_me(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int	print_words(char **dest, char *str, char c)
{
	int	start;
	int	end;
	int	word;

	start = 0;
	end = 0;
	word = 0;
	while (str[end] != '\0')
	{
		if (str[end] == c || str[end] == 0)
			start = end + 1;
		if (str[end] != c && (str[end + 1] == c || str[end + 1] == 0))
		{
			dest[word] = malloc(sizeof(char) * (end - start + 2));
			if (!dest[word])
				return (free_me(dest, word), 0);
			ft_strlcpy(dest[word], str + start, end - start + 2);
			word++;
		}
		end++;
	}
	dest[word] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*str;

	str = (char *)s;
	if (!s)
		return (NULL);
	ptr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!ptr)
		return (NULL);
	if (!print_words(ptr, str, c))
		return (NULL);
	return (ptr);
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{
	char **oui;

	int i = 0;
	(void) argc;
	oui = ft_split(argv[1], argv[2][0]);
	if (!oui)
		return (0);
	while(oui[i] != NULL)
	{
		printf("%s\n", oui[i]);
		i++;
	}

	return (0);
}*/
/*
1) Compter le nombre de mots dans la string
2) Alloc words = malloc une string (chaque lettre d'un mot)
3) Split = malloc le tableau de tableau
*/
