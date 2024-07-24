/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:40:22 by jewu              #+#    #+#             */
/*   Updated: 2024/07/23 17:19:21 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env *envp, char **env)
{
	envp->env = env;
	if (!env[0])
	{
		envp->path = copy_path(envp);
		envp->oldpwd = NULL;
		envp->pwd = get_current_path();
		envp->first_variable = NULL;
	}
	else
	{
		envp->path = copy_path(envp);
		envp->oldpwd = NULL;
		envp->pwd = get_current_path();
		envp->first_variable = NULL;
		init_chained_var(envp, env);
	}
}
