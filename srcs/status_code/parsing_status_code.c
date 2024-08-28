/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:24:00 by jewu              #+#    #+#             */
/*   Updated: 2024/08/28 14:18:14 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function to update exit status of the parsing according to flag
int	update_exit_status(t_shell *gear_5, int flag)
{
	if (flag == 2)
	{
		error("Error : syntax error\n");
		gear_5->exit_status = 2;
	}
	else if (flag == 1)
	{
		error("Error : memory allocation error\n");
		gear_5->exit_status = 1;
	}
	else if (flag == 0)
	{
		gear_5->exit_status = 0;
	}
	return (gear_5->exit_status);
}
