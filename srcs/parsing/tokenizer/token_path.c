/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:04:43 by jewu              #+#    #+#             */
/*   Updated: 2024/09/02 15:35:18 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_paths(char *tmp_path, char *cmd_path)
{
	if (!tmp_path || !cmd_path)
		return ;
	if (tmp_path)
	{
		free(tmp_path);
		tmp_path = NULL;
	}
	if (cmd_path)
	{
		free(cmd_path);
		cmd_path = NULL;
	}
}
/* Free tmp_path and cmd_path */

static int	join_paths(t_env *envp, t_token *token, int i)
{
	envp->tmp_path = ft_strjoin(envp->path[i], "/");
	if (!envp->tmp_path)
		return (FAILURE);
	envp->cmd_path = ft_strjoin(envp->tmp_path, token->word);
	if (!envp->cmd_path)
		return (FAILURE);
	if ((access(envp->cmd_path, F_OK) == 0)
		&& (access(envp->cmd_path, X_OK) == 0))
	{
		token->cmd_path = ft_strdup(envp->cmd_path);
		free_paths(envp->tmp_path, envp->cmd_path);
		return (SUCCESS);
	}
	free_paths(envp->tmp_path, envp->cmd_path);
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
			envp->cmd_path = NULL;
			return (SUCCESS);
		}
	}
	envp->cmd_path = NULL;
	return (FAILURE);
}
/* Is word an executable command? */
