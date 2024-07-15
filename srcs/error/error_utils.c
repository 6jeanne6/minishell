/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:43:14 by jewu              #+#    #+#             */
/*   Updated: 2024/07/15 18:44:25 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_env *envp, char	*message)
{
	if (!message)
	{
		clean_env(envp);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	clean_env(envp);
	exit(EXIT_FAILURE);
}
//customized message and free

void	clean_env(t_env *envp)
{
	int	i;

	i = 0;
	if (!envp->env[0])
	{
		free(envp->env_tmp[i]);
		free(envp->env_tmp);
	}
	i = 0;
	if (envp->path)
	{
		while (envp->path[i])
		{
			free(envp->path[i]);
			i++;
		}
		free(envp->path);
	}
}
//free envp structure