/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:04:43 by jewu              #+#    #+#             */
/*   Updated: 2024/07/25 17:56:41 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_paths(char *tmp_path, char *cmd_path)
{
	if (!tmp_path || !cmd_path)
		return ;
	if (tmp_path)
		free(tmp_path);
	if (cmd_path)
		free(cmd_path);
}
//free tmp_path and cmd_path

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
		token->cmd_path = envp->cmd_path;
		printf(GREEN"PATH is joined!\n"RESET);
		printf("YOUR WORKING PATH: %s\n", envp->cmd_path);
		free_paths(envp->tmp_path, envp->cmd_path);
		return (SUCCESS);
	}
	printf("path[%d]: %s\n", i, envp->cmd_path);
	free_paths(envp->tmp_path, envp->cmd_path);
	return (FAILURE);
}
//while loop to join path and word

int	check_path(t_env *envp, t_token *token)
{
	int		i;
	t_token	*current;

	i = 1;
	current = token;
	if (!envp->path || !current)
	{
		clean_env(envp);
		return (FAILURE);
	}
	while (current)
	{
		i = 1;
		while (envp->path[++i])
		{
			if (join_paths(envp, current, i) == SUCCESS)
				break ;
		}
		current = current->next;
	}
	envp->cmd_path = NULL;
	return (FAILURE);
}
//is word an executable command?
