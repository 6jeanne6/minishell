/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:31:54 by jewu              #+#    #+#             */
/*   Updated: 2024/07/16 22:12:09 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_append(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
			return (false);
		else if (input[i] == '>' && input[i + 1] == '>')
			return (true);
	}
	return (false);
}
//append chevron >>

bool	is_heredoc(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
			return (false);
		else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '>')
			return (false);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (true);
	}
	return (false);
}
//heredoc chevron <<

bool	is_output_chevron(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '>' && input[i + 1] != '>')
			return (true);
		else if (input[i] == '>' && input[i + 1] == '<')
			return (false);
	}
	return (false);
}
//output chevron: >

bool	is_input_chevron(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] != '<')
			return (true);
		else if (input[i] == '<' && input[i + 1] == '>')
			return (false);
	}
	return (false);
}
//input chevron: <

int	check_redirection(char *input)
{
	int	i;

	i = -1;

	while (input[++i])
	{
		if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
			return (FAILURE);
		if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
			return (FAILURE);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (SUCCESS);
		else if (input[i] == '>' && input[i + 1] == '>')
			return (SUCCESS);
		else if (input[i] == '<' && input[i + 1] != '<')
			return (SUCCESS);
		else if (input[i] == '>' && input[i + 1] != '>')
			return (SUCCESS);
	}
	return (FAILURE);
}
//checks if it is a redirection sign well done