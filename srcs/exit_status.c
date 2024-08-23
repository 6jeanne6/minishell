/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:24:00 by jewu              #+#    #+#             */
/*   Updated: 2024/08/23 16:09:41 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to update exit status according to flag
int	update_exit(int exit_status, int flag)
{
	if (flag == 1)
	{
		error("parsing error\n");
		exit_status = 1;
	}
	else if (flag == 2)
	{
		error("syntax error\n");
		exit_status = 2;
	}
	else if (flag == 126)
	{
		error("permission denied\n");
		exit_status = 126;
	}
	else if (flag == 127)
	{
		error("command not found\n");
		exit_status = 127;
	}
	else
		exit_status = -1;
	return (exit_status);
}
