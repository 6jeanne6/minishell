/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:12:05 by jewu              #+#    #+#             */
/*   Updated: 2024/09/19 16:57:52 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if function set_fd fails, clean exec
void	fail_set_fd_clean(t_exec *exec)
{
	if (!exec)
		return ;
	free_args_tab(exec->args);
	free(exec->cmd_name);
	free(exec);
}

//check if token is a redirection > >> < << or |
bool	token_is_redirection(t_token *token)
{
	if (!token)
		return (false);
	if (token->token_type == TOKEN_APPEND
		|| token->token_type == TOKEN_OUTPUT
		|| token->token_type == TOKEN_HEREDOC
		|| token->token_type == TOKEN_INPUT
		|| token->token_type == TOKEN_PIPE)
	{
		if (token->token_type == TOKEN_HEREDOC)
			token->has_heredoc = true;
		return (true);
	}
	return (false);
}

//put each word into an arg tab
void	set_arg_tab(t_exec *exec, t_token *token, t_env *envp,
int arg_count)
{
	t_token	*tmp;
	int		j;

	if (!token || !envp || arg_count == 0)
		return ;
	tmp = token;
	j = 0;
	exec->args[arg_count] = NULL;
	arg_count--;
	while (arg_count >= 0)
	{
		if (j == 0)
			exec->cmd_name = ft_strdup(tmp->word);
		exec->args[j] = ft_strdup(tmp->word);
		arg_count--;
		j++;
		tmp = tmp->next;
	}
}

//set fd_in or fd_out for t_structure
int	set_fd(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp)
{
	t_token	*head;

	if (!exec || !token || !envp)
		return (FAILURE);
	head = token;
	gear_5->j = 0;
	while (head && head->token_type != TOKEN_PIPE)
	{
		if (head->token_type == TOKEN_OUTPUT
			|| head->token_type == TOKEN_APPEND)
		{
			if (file_outfile(gear_5, exec, head) == FAILURE)
				return (FAILURE);
		}
		else if (head->token_type == TOKEN_INPUT
			|| head->token_type == TOKEN_HEREDOC)
		{
			if (file_input(gear_5, exec, head) == FAILURE)
				return (FAILURE);
		}
		head = head->next;
		gear_5->j++;
	}
	return (SUCCESS);
}
