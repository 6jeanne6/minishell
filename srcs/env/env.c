/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:40:22 by jewu              #+#    #+#             */
/*   Updated: 2024/07/09 16:27:43 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_path(t_env *envp)
{
	char	**search_path;

	search_path = NULL;
	if (!envp->env[0])
	{
		fetch_path(envp);
		search_path = split_path(envp, envp->env_tmp[0]);
	}
	else
		search_path = find_path(envp, search_path);
	return (search_path);
}
//init minishell to copy PATH
