/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:40:22 by jewu              #+#    #+#             */
/*   Updated: 2024/10/20 14:52:17 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialize pwd environment variable and add at variable env list. */
static void	init_pwd(t_env *envp)
{
	t_var	*variable;
	char	*current_path;
	char	*name;

	current_path = get_current_path();
	name = ft_strdup("PWD");
	if (!name)
		return ;
	variable = init_env_variable(name, current_path);
	add_variable_to_the_list(envp, variable);
}

/* Initialize PATH environment variable and add at variable env list. */
static void	init_path(t_env *envp)
{
	t_var		*variable;
	char		*name;
	char		*value;
	char		*tmp_value;

	name = ft_strdup("PATH");
	if (!name)
		return ;
	tmp_value = double_array_to_one_array(envp->path);
	if (!tmp_value)
	{
		free(name);
		return ;
	}
	value = trim_path(tmp_value, "PATH=\"");
	if (!value)
	{
		free(name);
		free(tmp_value);
		return ;
	}
	free(tmp_value);
	variable = init_env_variable(name, value);
	add_variable_to_the_list(envp, variable);
}

/* Setup the environment variable */
//	→ env -i
//	→ normal env
void	init_env(t_env *envp, char **env)
{
	envp->env = env;
	if (!env[0])
	{
		envp->env_i_flag = 1;
		envp->path = copy_path(envp);
		envp->first_variable = NULL;
		init_pwd(envp);
		init_path(envp);
	}
	else
	{
		envp->env_i_flag = 0;
		envp->path = copy_path(envp);
		envp->first_variable = NULL;
		init_chained_var(envp, env);
	}
}
