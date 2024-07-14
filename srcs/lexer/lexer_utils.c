/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:50:53 by jewu              #+#    #+#             */
/*   Updated: 2024/07/14 22:06:39 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	i_am_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
//check if it's space or tab

bool	backslash_null(char c)
{
	if (c == '\0')
		return (true);
	return (false);
}
//check if we are in end of string \0