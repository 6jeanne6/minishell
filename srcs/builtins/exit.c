/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:08:26 by jewu              #+#    #+#             */
/*   Updated: 2024/09/23 17:02:31 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check digit */
static int	status_generator(char *str)
{
	int	status;

	status = ft_atoi(str);
	if (status >= 0 && status <= 255)
	{
		return (status);
	}
	else
	{
		status = status % 256;
		if (status < 0)
			status += 256;
		return (status);
	}
}

/* Handles the case where `exit` has exactly two arguments. */
static void	handle_two_arg(t_shell *gear_5, t_exec *execution,
			t_env *envp, t_exec *exec)
{
	int	status;

	status = status_generator(execution->args[1]);
	if (status >= 0 && status <= 255)
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd("\n", 2);
		gear_5->exit_status = status;
		execve_clean_all(exec, envp, gear_5);
		exit(status);
	}
	else
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd("\n", 2);
		execve_clean_all(exec, envp, gear_5);
		exit(status);
	}
}

/* Handles the case where `exit` has only one argument. */
static void	handle_one_arg(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	gear_5->exit_status = 0;
	ft_putstr_fd("exit", 2);
	ft_putstr_fd("\n", 2);
	execve_clean_all(exec, envp, gear_5);
	exit(0);
}

/* Handles the case where `exit` has more than two arguments. */
static void	handle_multiple_args(t_shell *gear_5)
{
	gear_5->exit_status = 1;
	ft_putstr_fd("exit", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("exit: too many arguments", 2);
	ft_putstr_fd("\n", 2);
}

/* Main exit function handling different argument counts. */
void	exit_builtin(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	int	i;

	if (!exec || !gear_5)
		return ;
	i = 0;
	while (exec->args[i])
		i++;
	if (i > 2)
	{
		handle_multiple_args(gear_5);
		return ;
	}
	else if (i == 1)
		handle_one_arg(gear_5, envp, exec);
	else if (i == 2)
	{
		quit_if_exit_arg_is_not_numeric(exec->args[1], gear_5, envp, exec);
		handle_two_arg(gear_5, exec, envp, exec);
	}
}
