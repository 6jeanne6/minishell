/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_order_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:14 by jewu              #+#    #+#             */
/*   Updated: 2024/09/22 17:01:05 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks tokens around pipe
int	pipe_order(t_token *token, t_shell *gear_5)
{
	if (!gear_5 || !token)
		return (FAILURE);
	if (token->token_type == TOKEN_PIPE)
	{
		if (!token->next || !token->previous)
		{
			update_exit_status(gear_5, 2, NULL);
			return (FAILURE);
		}
		if (token->next)
		{
			if (token->next->token_type == TOKEN_PIPE)
			{
				update_exit_status(gear_5, 2, NULL);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

//when file does not exist display an error message
void	filename_error(char *name, char *message, t_shell *gear_5, int flag)
{
	if (!message)
		return ;
	if (flag == 1)
	{
		error(name);
		error(": ");
		error(message);
		error("\n");
		gear_5->exit_status = 1;
	}
	else if (flag == 2)
	{
		error(message);
		error("\n");
		gear_5->exit_status = 2;
	}
}
