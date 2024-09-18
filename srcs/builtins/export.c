/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:02:33 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/18 18:59:02 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Change and free the current var value */
static int	change_env_var_valuee(t_env *env, char *var_name, char *new_value)
{
	t_var	*var;

	var = env->first_variable;
	while (var)
	{
		if (ft_strcmp(var->variable_name, var_name) == 0)
		{
			if (var->variable_value)
				free(var->variable_value);
			var->variable_value = new_value;
			return (1);
		}
		var = var->next;
	}
	return (0);
}

/* Check if the variable is in the list */
static int	variable_exist(t_env *env, char *variable_name)
{
	t_var	*var;

	var = env->first_variable;
	while (var)
	{
		if (ft_strcmp(var->variable_name, variable_name) == 0)
			return (1);
		var = var->next;
	}
	return (0);
}

/* Change or create variable */
static void	change_or_create_var(t_env *env, char *name, char *value)
{
	t_var	*variable;

	if (variable_exist(env, name))
	{
		change_env_var_valuee(env, name, value);
		free(name);
	}
	else
	{
		variable = init_env_variable(name, value);
		add_variable_to_the_list(env, variable);
	}
}

/* Print all environment variables */
static void	print_all_env_var(t_env *env, int fd_out)
{
	t_var	*var;

	var = env->first_variable;
	while (var)
	{
		ft_putstr_fd("export ", fd_out);
		ft_putstr_fd(var->variable_name, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(var->variable_value, fd_out);
		ft_putstr_fd("\n", fd_out);
		var = var->next;
	}
}

// Print all variable values if it's only export 
// ELSE check if the variable exists, 
// if the variable exists change else add to the list
int	export(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	char	*name;
	char	*value;
	int		i;

	if (!exec->args[1] || (ft_strlen(exec->args[1]) == 0 && !exec->args[2]))
	{
		print_all_env_var(envp, exec->fd_out);
		gear_5->exit_status = 0;
		return (0);
	}
	i = 1;
	while (exec->args[i])
	{
		name = get_variable_name(exec->args[i]);
		if (is_valid_identifier(name, gear_5, 1) == FAILURE)
			return (FAILURE);
		value = get_variable_value(exec->args[i]);
		if (!value)
			value = ft_strdup("");
		change_or_create_var(envp, name, value);
		i++;
	}
	gear_5->exit_status = 0;
	return (0);
}
