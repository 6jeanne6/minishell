/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:08:26 by jewu              #+#    #+#             */
/*   Updated: 2024/09/16 15:24:50 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check digit */
static int	is_digital(int digit)
{
	if (digit < 0 || digit > 2147483646)
		return (0);
	return (1);
}

/* Handles the case where `exit` has exactly two arguments. */
static void	handle_two_arg(t_shell *gear_5, t_exec *execution, t_env *envp)
{
	int	status;

	status = ft_atoi(execution->args[1]);
	if (is_digital(status) == 0)
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd("\n", 2);
		error("bash: exit: ");
		error(execution->args[1]);
		error(": positive numeric argument required");
		gear_5->exit_status = 2;
		clean_env(envp);
		free_exec(execution);
		exit(2);
	}
	else
	{
		ft_putstr_fd("exit", 2);
		ft_putstr_fd("\n", 2);
		clean_env(envp);
		free_exec(execution);
		exit(status);
	}
}

/* Handles the case where `exit` has only one argument. */
static void	handle_one_arg(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	gear_5->exit_status = 0;
	ft_putstr_fd("exit", 2);
	ft_putstr_fd("\n", 2);
	clean_env(envp);
	free_exec(exec);
	exit(0);
}

/* Handles the case where `exit` has more than two arguments. */
static void	handle_multiple_args(t_shell *gear_5)
{
	gear_5->exit_status = 1;
	ft_putstr_fd("exit", 2);
	ft_putstr_fd("\n", 2);
	error("bash: exit: too many arguments");
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
		handle_two_arg(gear_5, exec, envp);
}
