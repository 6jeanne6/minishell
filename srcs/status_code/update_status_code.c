/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:43 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/14 16:16:59 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

// → 126 = permission denied
// → 127 = command not found, or no such file or directory for /bin/ls
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
	else if (flag == 127 && name[0] == '/')
	{
		error(name);
		error(": ");
		error("no such file or directory\n");
		gear_5->exit_status = 127;
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

//function to update exit status according to flag
// → 2 = syntax error
// → 1 = error
// → 126 = permission denied
// → 127 = command not found, or no such file or directory for /bin/ls
// → 130 = SIGINT ctrl-C
// → 131 = SIGQUIT ctrl-backslash
// → 0 = SUCCESS
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

// Function that display status code
static void	display_error(int exit_status)
{
	if (exit_status == 130)
		error(": command not found");
	else if (exit_status == 131)
		error(": command not found");
	else if (exit_status == 127)
		error(": command not found");
	else if (exit_status == 126)
		error(": permission denied");
	else if (exit_status == 2)
		error(": syntax error");
	else if (exit_status == 1)
		error(": execution failed, command not found or syntax error");
	else if (exit_status == 0)
		error(": command not found");
	else if (exit_status)
		error(": command not found");
}

//if prompt is $?, display exit status code and error message
int	is_dollar_question_mark_input(t_shell *gear_5, int *flag)
{
	char	*status_code;

	status_code = ft_itoa(gear_5->exit_status);
	if (!status_code)
		return (FAILURE);
	if (ft_strcmp(gear_5->input, "$?") == 0)
	{
		error(status_code);
		display_error(gear_5->exit_status);
		*flag = 1;
		free(status_code);
		printf("\n");
		return (SUCCESS);
	}
	free(status_code);
	return (FAILURE);
}
