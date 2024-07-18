/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_detection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:36:41 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/07/17 18:08:08 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_variable(const char *input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == '\0')
		return (false);
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\0' && input[i + 1] != ' ')
			return (true);
		i++;
	}
	return (false);
}

bool	is_variable_declaration(const char *input)
{
	int	i;

	i = 0;
	if (input == NULL || *input == '\0')
		return (false);
	while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_'))
		i++;
	if (input[i] == '=')
		return (true);
	else
		return (false);
}
