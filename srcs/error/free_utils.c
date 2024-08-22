/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:35:16 by jewu              #+#    #+#             */
/*   Updated: 2024/08/22 19:42:56 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free token list + free the ft_strdup of temp->cmd_path
void	super_free_token_list(t_token *head)
{
	t_token	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->cmd_path)
			free(temp->cmd_path);
		free(temp->word);
		free(temp);
		temp = NULL;
	}
}

//free when init_exec failed
void	free_t_exec(t_token *token, t_env *envp)
{
	if (!envp || !token)
		return ;
	super_free_token_list(token);
	free_envp_path(envp);
}

//free tmp path and cmd path
void	free_envp_path(t_env *envp)
{
	if (!envp)
		return ;
	if (envp->cmd_path)
		envp->cmd_path = NULL;
}

//free token list when token order is wrong
void	wrong_token_order(t_token *token, t_env *envp)
{
	if (!token || !envp)
		return ;
	free_token_list(token);
}
