/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:37:37 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/05 19:17:40 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_max_index(t_token *list)
{
	t_token *begin_list;
	int		count;
	begin_list = list;
	count = 0;
	while (begin_list != NULL)
	{
		count+=1;
		begin_list = begin_list -> next;
	}
	return (count);
}
static void indexor(t_token *list)
{
	t_token *current;
	current = list;
	while (current != NULL)
	{
		current->index += 1;
		current = current -> next;
	}
}
static t_cmd	init_cmd(t_token *list)
{
	t_cmd	*cmd;

	cmd->id = list->token_type;
	cmd->in_double_quote = list->in_double_quote;
	cmd->outer_single_quote = list->outer_double_quote;
	cmd->bin = NULL;
	cmd->args = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->first_arg = NULL;
	cmd->pid = 0;
}

int	define_class(t_token *list)
{
	if (token->token_type == TOKEN_CMD)
	{
		token->class = ((t_cmd *)token->class);
		return (init_cmd(list));
	}
	if (token->token_type == TOKEN_PIPE || token->token_type == TOKEN_APPEND
		token->token_type == TOKEN_INPUT || token->token_type == TOKEN_OUTPUT
		|| token->token_type == TOKEN_APPEND)
	{
		token->class = ((t_redir *)token->class);
		init_token
	}
	if (token->token_type == TOKEN_FILE)
	{
		token->class = ((t_file *)token->class);
		init_file
	}
}

void	init_struct(t_token *list)
{
	t_token	*current;
	int		index_max;
	int		index;

	current = list;
	indexor(list);
	index = 1;
	index_max = get_max_index(list);
	while (index <= index_max)
	{
		index = define_class(list);
		current = list -> next;
	}
}
