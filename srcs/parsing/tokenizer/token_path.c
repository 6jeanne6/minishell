/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:04:43 by jewu              #+#    #+#             */
/*   Updated: 2024/08/22 19:41:14 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	join_paths(t_env *envp, t_token *token, int i)
{
	envp->tmp_path = ft_strjoin(envp->path[i], "/");
	if (!envp->tmp_path)
		return (FAILURE);
	envp->cmd_path = ft_strjoin(envp->tmp_path, token->word);
	free(envp->tmp_path);
	if (!envp->cmd_path)
		return (FAILURE);
	if ((access(envp->cmd_path, F_OK) == 0)
		&& (access(envp->cmd_path, X_OK) == 0))
	{
		token->cmd_path = ft_strdup(envp->cmd_path);
		if (!token->cmd_path)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}
/* While loop to join path and word */

int	check_path(t_env *envp, t_token *token)
{
	int	i;

	i = 1;
	if (!envp->path || !token)
	{
		clean_env(envp);
		return (FAILURE);
	}
	while (envp->path[++i])
	{
		if (join_paths(envp, token, i) == SUCCESS)
		{
			free(envp->cmd_path);
			return (SUCCESS);
		}
		if (envp->cmd_path)
			free(envp->cmd_path);
	}
	envp->tmp_path = NULL;
	envp->cmd_path = NULL;
	token->cmd_path = NULL;
	return (FAILURE);
}
/* Is word an executable command? */
