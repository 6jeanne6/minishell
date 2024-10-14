/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:40:22 by jewu              #+#    #+#             */
/*   Updated: 2024/10/09 13:59:32 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initialize pwd environment variable. */
static void	init_pwd(t_env *envp)
{
	t_var	*variable;
	char	*current_path;

	current_path = get_current_path();
	variable = init_env_variable("pwd", current_path);
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
		envp->path = copy_path(envp);
		envp->first_variable = NULL;
		init_pwd(envp);
	}
	else
	{
		envp->path = copy_path(envp);
		envp->first_variable = NULL;
		init_chained_var(envp, env);
	}
}
