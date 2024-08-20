/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:12:05 by jewu              #+#    #+#             */
/*   Updated: 2024/08/21 00:04:38 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exec->args[j] = ft_strdup(tmp->word);
		arg_count--;
		j++;
		tmp = tmp->next;
	}
}

//set fd_in or fd_out for t_structure
void	set_fd(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp)
{
	if (!exec || !token || !envp)
		return ;
	exec->fd_in = STDIN_FILENO;
	exec->fd_out = STDOUT_FILENO;
	if (token->token_type == TOKEN_OUTPUT || token->token_type == TOKEN_APPEND)
	{
		if (file_outfile(gear_5, exec, token) == SUCCESS)
			return ;
	}
	// else if (token->token_type == TOKEN_INPUT || token->token_type == TOKEN_HEREDOC)
	// {
	// 	if (file_input(exec, token) == SUCCESS)
	// 		return ;
	// }
}
