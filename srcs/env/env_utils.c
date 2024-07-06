/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:24:03 by jewu              #+#    #+#             */
/*   Updated: 2024/07/06 19:41:56 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(t_env *envp, char *str)
{
	char	**ptr;

	ptr = ft_split(str, ':');
	if (!ptr)
		clean_env(envp);
	return (ptr);
}
//split the PATH into sub_paths

void	find_path(t_env *envp)
{
	int	i;

	i = 0;
	if (!envp || !envp->env)
		ft_putstr_fd("No environment!\n", 2);
	while (envp->env[i] && (ft_strnstr(envp->env[i], "PATH=", 5) == 0))
		i++;
	envp->path = split_path(envp, envp->env[i]);
}
//check the PATH
