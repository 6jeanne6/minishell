/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:20:28 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/14 19:51:37 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ignore n
static int	is_a_noption(char *args)
{
	int	i;

	i = 0;
	if (args[i] == '-')
	{
		i++;
		if (args[i++] == 'n')
		{
			while (args[i] && args[i] == 'n')
				i++;
			if (args[i] == '\0')
				return (true);
		}
	}
	return (false);
}

//init echo
static void	init_echo(t_exec *exec, int *i, int *new_line)
{
	*new_line = 1;
	*i = 1;
	while (exec->args[*i] && is_a_noption(exec->args[*i]))
	{
		*new_line = 0;
		*i += 1;
	}
}

//echo pipe write in the STDOUT that was DUP2
int	echo_pipe(t_shell *gear_5, t_exec *exec)
{
	int	i;
	int	new_line;

	init_echo(exec, &i, &new_line);
	while (exec->args[i])
	{
		ft_putstr_fd(exec->args[i], STDOUT_FILENO);
		if (exec->args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	gear_5->exit_status = 0;
	return (0);
}

//print message
int	echo(t_shell *gear_5, t_exec *exec)
{
	int	i;
	int	new_line;

	init_echo(exec, &i, &new_line);
	while (exec->args[i])
	{
		ft_putstr_fd(exec->args[i], exec->fd_out);
		if (exec->args[i + 1] != NULL)
			ft_putstr_fd(" ", exec->fd_out);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", exec->fd_out);
	gear_5->exit_status = 0;
	return (0);
}
