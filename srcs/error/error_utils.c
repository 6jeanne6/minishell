/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:43:14 by jewu              #+#    #+#             */
/*   Updated: 2024/07/31 18:33:49 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *head)
{
	t_token	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->word);
		free(temp);
	}
}

void	error(char	*message)
{
	if (!message)
		return ;
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
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
	free_var_list(envp);
	free(envp->pwd);
	if (envp->oldpwd)
		free(envp->oldpwd);
}

//free envp structure