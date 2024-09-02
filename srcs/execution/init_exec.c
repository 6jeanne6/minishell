/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:00:38 by jewu              #+#    #+#             */
/*   Updated: 2024/09/02 15:08:09 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//linked list t_exec
static t_exec	*link_exec_nodes(t_exec *prev_exec, t_exec *exec)
{
	if (prev_exec)
	{
		prev_exec->next = exec;
		exec->prev = prev_exec;
	}
	else
		exec->prev = NULL;
	exec->next = NULL;
	return (exec);
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
	set_arg_tab(exec, token, envp, arg_count);
	return (exec);
}

static int	count_arguments_find_redirection(t_token **head, t_token **start)
{
	int		arg_count;
	t_token	*tmp;

	arg_count = 0;
	tmp = *head;
	*start = *head;
	while (tmp && token_is_redirection(tmp) == false)
	{
		tmp = tmp->next;
		arg_count++;
	}
	while (*head && token_is_redirection(*head) == false)
	{
		if ((*head)->next)
			*head = (*head)->next;
		else
			break ;
	}
	return (arg_count);
}

//go through token list
static t_exec	*process_tokenn(t_shell *gear_5, t_token **head, t_env *envp)
{
	int		arg_count;
	t_token	*start;
	t_exec	*exec;

	arg_count = count_arguments_find_redirection(head, &start);
	if (start != *head || arg_count > 0)
	{
		exec = set_structure(gear_5, start, envp, arg_count);
		if (!exec)
			return (NULL);
	}
	else
		return (NULL);
	if (set_fd(gear_5, exec, *head, envp) == FAILURE)
		return (free_args_tab(exec->args), free(exec), NULL);
	while (*head)
	{
		if ((*head)->token_type == TOKEN_PIPE)
		{
			*head = (*head)->next;
			break ;
		}
		*head = (*head)->next;
	}
	return (exec);
}

//init t_exec with data we already have with tokens
t_exec	*init_exec(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_exec	*prev_exec;
	t_exec	*exec;
	t_exec	*exec_list;
	t_token	*start;

	if (!gear_5 || !token || !envp)
		return (NULL);
	prev_exec = NULL;
	exec = NULL;
	while (token)
	{
		start = token;
		exec = process_tokenn(gear_5, &token, envp);
		if (exec)
		{
			if (prev_exec == NULL)
				exec_list = exec;
			else
				exec = link_exec_nodes(prev_exec, exec);
			prev_exec = exec;
			exec->bin = start->cmd_path;
		}
		else
			return (NULL);
	}

	// int i = 0;
	// int j = 1;
	// t_exec *lol = exec_list;
	// if (!lol)
	// 	return (NULL);
	// while (lol)
	// {
	// 	i = 0;
	// 	printf("%dth t_exec\n", j);
	// 	while (lol->args && lol->args[i])
	// 	{
	// 		printf("arg[%d]: %s\n", i, lol->args[i]);
	// 		i++;
	// 	}
	// 	printf("arg[%d]: %s\n", i, lol->args[i]);
	// 	printf("fd_out: %d\n", lol->fd_out);
	// 	lol = lol->next;
	// 	j++;
	// }
	return (exec_list);
}
