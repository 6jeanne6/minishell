/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:00:38 by jewu              #+#    #+#             */
/*   Updated: 2024/08/15 19:51:07 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//linked list t_exec
static void	link_exec(t_exec *prev_exec, t_exec *exec)
{
	if (prev_exec)
		prev_exec->next = exec;
	exec->prev = prev_exec;
	exec->next = NULL;
}

//malloc t_exec structure with data provided
static t_exec	*set_structure(t_shell *gear_5, t_token *token, t_env *envp,
int arg_count)
{
	t_exec	*exec;

	if (!token || !envp || arg_count == 0)
		return (NULL);
	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!exec->args)
	{
		free(exec);
		return (NULL);
	}
	(void)gear_5;
	//if (set_fd(gear_5, exec, token, envp) == SUCCESS)
	set_arg_tab(exec, token, envp, arg_count);
	return (exec);
}

//check if token is a redirection > >> < << or |
static bool	is_redirection(t_token *token)
{
	if (!token)
		return (false);
	if (token->token_type == TOKEN_APPEND
		|| token->token_type == TOKEN_OUTPUT
		|| token->token_type == TOKEN_HEREDOC
		|| token->token_type == TOKEN_INPUT
		|| token->token_type == TOKEN_PIPE)
		return (true);
	return (false);
}

//go through token list
static t_exec	*process_token(t_shell *gear_5, t_token **head, t_env *envp)
{
	int		arg_count;
	t_token	*start;
	t_exec	*exec;

	arg_count = 0;
	start = *head;
	while (*head && is_redirection(*head) == false)
	{
		*head = (*head)->next;
		arg_count++;
	}
	if (start != *head || arg_count > 0)
	{
		exec = set_structure(gear_5, start, envp, arg_count);
		if (!exec)
			return (NULL);
	}
	else
		return (NULL);
	if (*head && is_redirection(*head) == true)
		*head = (*head)->next;
	return (exec);
}

//init t_exec with data we already have with tokens
t_exec	*init_exec(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*head;
	t_exec	*prev_exec;
	t_exec	*exec;

	if (!gear_5 || !token || !envp)
		return (NULL);
	head = token;
	prev_exec = NULL;
	exec = NULL;
	while (head)
	{
		exec = process_token(gear_5, &head, envp);
		if (exec)
		{
			link_exec(prev_exec, exec);
			prev_exec = exec;
		}
	}
	// int i = 0;
	// int j = 1;
	// t_exec *lol = exec;
	// while (lol)
	// {
	// 	i = 0;
	// 	printf("%dth t_exec\n", j);
	// 	while (lol->args && lol->args[i])
	// 	{
	// 		printf("%dth t_exec again\n", j);
	// 		printf("arg[%d]: %s\n", i, lol->args[i]);
	// 		i++;
	// 	}
	// 	lol = lol->next;
	// 	j++;
	// }
	return (exec);
}
