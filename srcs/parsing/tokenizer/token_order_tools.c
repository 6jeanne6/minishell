/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_order_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:34:14 by jewu              #+#    #+#             */
/*   Updated: 2024/09/18 12:47:24 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
