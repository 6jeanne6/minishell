/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:00:38 by jewu              #+#    #+#             */
/*   Updated: 2024/10/10 13:50:26 by jewu             ###   ########.fr       */
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
static t_exec	*set_structure(t_token *token, t_env *envp, int arg_count)
{
	t_exec	*exec;
	t_token	*start;

	if (!token || !envp)
		return (NULL);
	exec = ft_calloc(1, sizeof(t_exec));
	start = token;
	if (!exec)
		return (NULL);
	exec->args = ft_calloc(arg_count + 1, sizeof(char *));
	if (!exec->args)
		return (free(exec), NULL);
	while (start && start->token_type != TOKEN_PIPE)
	{
		if (start->token_type == TOKEN_CMD && start->cmd_path)
			exec->bin = ft_strdup(start->cmd_path);
		start = start->next;
	}
	set_arg_tab(exec, token, envp, arg_count);
	exec->fd_in = STDIN_FILENO;
	exec->fd_out = STDOUT_FILENO;
	return (exec);
}

//how many commands, arguments and redirections for ONE t_exec
// • normal:
//		→ stop until | or redirection is encountered
// • echo:
//		→ counts ARG and BUILTIN until | is encountered
static int	count_arguments_find_redirection(t_token **head, t_token *tmp)
{
	int		arg_count;

	arg_count = 0;
	tmp = *head;
	while (tmp && tmp->token_type != TOKEN_PIPE)
	{
		if (token_is_redirection(tmp) == false && tmp->token_type != TOKEN_FILE)
			arg_count++;
		tmp = tmp->next;
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
	t_token	*tmp;
	t_exec	*exec;

	start = *head;
	tmp = *head;
	arg_count = count_arguments_find_redirection(head, tmp);
	if (start != *head || start->token_type == TOKEN_HEREDOC || arg_count > 0)
	{
		exec = set_structure(start, envp, arg_count);
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
		}
		else
			return (NULL);
	}
	return (exec_list);
}
