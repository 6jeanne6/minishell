/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:43 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/12 18:48:12 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_exit_status_exec(t_shell *gear_5, int flag, char *name)
{
	if (!flag || !name)
		return (FAILURE);
	if (flag == 126)
	{
		error(name);
		error(": ");
		error("permission denied\n");
		gear_5->exit_status = 126;
	}
	else if (flag == 127)
	{
		error(name);
		error(": ");
		error("command not found\n");
		gear_5->exit_status = 127;
	}
	return (gear_5->exit_status);
}

//exit status 1
static void	exit_one(t_shell *gear_5, char *name)
{
	if (!gear_5)
		return ;
	if (name)
	{
		error(name);
		error(": ");
		error("permission denied\n");
	}
	else
		error("Error : check your input\n");
	gear_5->exit_status = 1;
}

//function to update exit status of the parsing according to flag
int	update_exit_status(t_shell *gear_5, int flag, char *name)
{
	if (flag == 2)
	{
		error("Error : syntax error\n");
		gear_5->exit_status = 2;
	}
	else if (flag == 1)
		exit_one(gear_5, name);
	else if (flag == 126 || flag == 127)
	{
		if (update_exit_status_exec(gear_5, flag, name) == FAILURE)
			return (FAILURE);
	}
	else if (flag == 0)
		gear_5->exit_status = 0;
	return (gear_5->exit_status);
}

int	is_dollar_question_mark_input(t_shell *gear_5)
{
	if (ft_strcmp(gear_5->input, "$?") == 0)
	{
		printf("%d\n", gear_5->exit_status);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	update_exit_status_code(t_shell *gear_5)
{
	if (is_dollar_question_mark_input(gear_5) == SUCCESS)
		return (SUCCESS);
	else
		gear_5->exit_status = 0;
	return (FAILURE);
}
