/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:35:16 by jewu              #+#    #+#             */
/*   Updated: 2024/10/21 16:55:01 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free each node in token linked list + free cmd_path
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

//free each node in token linked list
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

//free token list when token order is wrong
void	wrong_token_order(t_token *token, t_env *envp, t_shell *gear_5)
{
	(void)gear_5;
	if (!token || !envp)
		return ;
	super_free_token_list(token);
}
