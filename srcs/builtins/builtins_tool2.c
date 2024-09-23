/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tool2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:51:23 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/21 17:54:47 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quit_and_clean(char *str, t_shell *gear_5,
			t_env *envp, t_exec *exec)
{
	ft_putstr_fd("exit", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required", 2);
	ft_putstr_fd("\n", 2);
	gear_5->exit_status = 2;
	execve_clean_all(exec, envp, gear_5);
	exit (2);
}

void	quit_if_exit_arg_is_not_numeric(char *str, t_shell *gear_5,
		t_env *envp, t_exec *exec)
{
	int	i;
	int	sign_count;

	i = 0;
	sign_count = 0;
	while (str[i] == '+' || str[i] == '-')
	{
		i++;
		sign_count++;
	}
	if (sign_count > 1)
		quit_and_clean(str, gear_5, envp, exec);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			quit_and_clean(str, gear_5, envp, exec);
		}
		i++;
	}
}
