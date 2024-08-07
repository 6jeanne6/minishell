/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:03:09 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/07 13:56:15 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
/* Check syntax of $environment variable */

int	is_variable_declaration(const char *input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == '\0')
		return (FAILURE);
	if (!ft_isalphanum(input[i]) && input[i] != '_')
		return (FAILURE);
	 if (input[i] == '_' && input[i + 1] == '=')
        return (FAILURE);
	while (input[i] != '\0' && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	if (input[i] == '='
		&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_')
		&& input[i + 1] != '\0')
		return (SUCCESS);
	return (FAILURE);
}
/* Check syntax of variable assignant name=value */