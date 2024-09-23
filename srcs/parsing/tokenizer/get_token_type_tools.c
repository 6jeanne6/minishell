/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/23 11:58:31 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/* Check syntax of $environment variable */
int	is_variable(const char *input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == '\0')
		return (FAILURE);
	if (input[i] == '$')
		i++;
	else
		return (FAILURE);
	if (input[i] == '\0')
		return (FAILURE);
	while (input[i])
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/* Check syntax of variable assignant name=value or name= */
int	is_variable_declaration(const char *input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == '\0')
		return (FAILURE);
	if (!ft_isalpha(input[i]) && input[i] != '_')
		return (FAILURE);
	if (input[i] == '_' && input[i + 1] == '=')
		return (FAILURE);
	while (input[i] != '\0' && input[i] != '=')
	{
		if (!ft_isalnum(input[i]))
		{
			if (input[i] != '_')
				return (FAILURE);
		}
		i++;
	}
	if (input[i] == '=')
		return (SUCCESS);
	return (FAILURE);
}

/* Check if its a file*/
int	is_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}
