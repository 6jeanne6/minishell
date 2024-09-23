/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:00:38 by jewu              #+#    #+#             */
/*   Updated: 2024/09/23 11:48:23 by jewu             ###   ########.fr       */
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
		if (exec->prev->has_pipe == true)
			exec->has_pipe = true;
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

	if (!token || !envp)
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
	exec->fd_in = STDIN_FILENO;
	exec->fd_out = STDOUT_FILENO;
	return (exec);
}

//how many commands, arguments and redirections for ONE t_exec
static int	count_arguments_find_redirection(t_token **head)
{
	int		arg_count;
	t_token	*tmp;

	arg_count = 0;
	tmp = *head;
	while (tmp && token_is_redirection(tmp) == false)
	{
		tmp = tmp->next;
		arg_count++;
	}
	while (*head && (*head)->token_type != TOKEN_PIPE)
		*head = (*head)->next;
	if (*head && (*head)->token_type == TOKEN_PIPE)
		*head = (*head)->next;
	return (arg_count);
}

//go through token list
static t_exec	*process_tokenn(t_shell *gear_5, t_token **head, t_env *envp)
{
	int		arg_count;
	t_token	*start;
	t_exec	*exec;

	start = *head;
	arg_count = count_arguments_find_redirection(head);
	if (start != *head || start->token_type == TOKEN_HEREDOC || arg_count > 0)
	{
		exec = set_structure(gear_5, start, envp, arg_count);
		if (!exec)
			return (NULL);
	}
	else
		return (NULL);
	if (*head)
	{
		if ((*head)->previous->token_type == TOKEN_PIPE)
			exec->has_pipe = true;
	}
	if (set_fd(gear_5, exec, start, envp) == FAILURE && exec->has_pipe == false)
		return (fail_set_fd_clean(exec), NULL);
	return (exec);
}

//init t_exec with data we already have with tokens
t_exec	*init_exec(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_exec	*prev_exec;
	t_exec	*exec;
	t_exec	*exec_list;
	t_token	*start;

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
			if (start->cmd_path)
				exec->bin = ft_strdup(start->cmd_path);
		}
		else
			return (NULL);
	}
	return (exec_list);
}
