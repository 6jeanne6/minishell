/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:31:54 by jewu              #+#    #+#             */
/*   Updated: 2024/07/15 16:32:15 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_append(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (true);
	}
	return (false);
}
//append chevron >>

static bool	is_heredoc(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
			return (true);
	}
	return (false);
}
//heredoc chevron <<

static bool	is_output_chevron(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '>' && input[i + 1] != '>')
			return (true);
	}
	return (false);
}
//output chevron: >

static bool	is_input_chevron(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] != '<')
			return (true);
	}
	return (false);
}
//input chevron: <

int	is_redirection(char *input)
{
	if ((is_input_chevron(input) == true) || (is_output_chevron(input) == true)
		|| (is_append(input) == true) || (is_heredoc(input) == true))
		return (SUCCESS);
	return (FAILURE);
}
//checks if it is a redirection sign well done