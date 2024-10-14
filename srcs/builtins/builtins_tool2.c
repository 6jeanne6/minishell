/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tool2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:51:23 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/11 18:05:52 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check if number if longer than int
int	is_num_overflow(char *str)
{
	int	len;
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	len = ft_strlen(str + i);
	if (len > 19)
		return (1);
	if (len == 19)
	{
		if (str[0] == '-')
		{
			if (ft_strcmp(str + i, "9223372036854775808") > 0)
				return (1);
		}
		else
		{
			if (ft_strcmp(str + i, "9223372036854775807") > 0)
				return (1);
		}
	}
	return (0);
}

//remove all sub-paths in envp
void	unset_path(t_env *envp)
{
	int	i;

	i = 0;
	if (envp->path)
	{
		while (envp->path[i])
		{
			free(envp->path[i]);
			envp->path[i] = NULL;
			i++;
		}
		free(envp->path);
		envp->path = NULL;
	}
}

//change PATH variable in envp
void	handle_path(t_env *envp, char *arg)
{
	char	*name;
	char	*value;
	char	**new_paths;

	name = get_variable_name(arg);
	if (check_var_name(name) == 0)
	{
		free(name);
		return ;
	}
	if (ft_strcmp(name, "PATH") != 0)
	{
		free(name);
		return ;
	}
	value = get_variable_value(arg);
	if (!value)
		value = ft_strdup("");
	unset_path(envp);
	new_paths = split_path(envp, value);
	envp->path = new_paths;
	free(name);
	free(value);
}

//for exit builtin, clean envp and then exit if arg is not number
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

//for exit builtin, clean envp and then exit
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
			quit_and_clean(str, gear_5, envp, exec);
		i++;
	}
}
