/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:20:28 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/18 18:59:20 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_echo(t_exec *exec, int *i, int *new_line)
{
	if (exec->args[1] && ft_strcmp(exec->args[1], "-n") == 0)
	{
		*new_line = 0;
		*i = 2;
	}
	else
	{
		*new_line = 1;
		*i = 1;
	}
}

int	echo(t_shell *gear_5, t_exec *exec)
{
	int	i;
	int	new_line;

	init_echo(exec, &i, &new_line);
	while (exec->args[i])
	{
		if (ft_strcmp(exec->args[i], "-n") == 0)
		{
			i++;
			continue ;
		}
		if (ft_strcmp(exec->args[i], "$?") == 0
			&& exec->outer_single_quote != 1)
			ft_putnbr_fd(gear_5->exit_status, exec->fd_out);
		else
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
