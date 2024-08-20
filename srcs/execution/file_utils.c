/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:21:14 by jewu              #+#    #+#             */
/*   Updated: 2024/08/21 00:06:53 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle <<
static int	handle_heredoc(t_exec *exec, t_token *token)
{
	if (!exec || !token)
		return (FAILURE);
}

//handle <
static int	handle_input(t_exec *exec, t_token *token)
{
	if (!exec || !token)
		return (FAILURE);
}

//check rights for input file in <
int	file_input(t_exec *exec, t_token *token)
{
	if (!exec || !token)
		return (FAILURE);
	if (token->token_type == TOKEN_INPUT)
	{
		if (handle_input(exec, token) == FAILURE)
			return (FAILURE);
	}
	else if (token->token_type == TOKEN_HEREDOC)
	{
		if (handle_heredoc(exec, token) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

//check if we can write into the file
static void	write_permission(t_shell *gear_5, char *file)
{
	if (!gear_5 || !file)
		return ;
	if (access(file, W_OK) == -1)
	{
		gear_5->exit_status = 1;
		ft_putstr_fd(YELLOW"file: ", STDERR_FILENO);
		error("permission denied\n");
	}
}

//check rights for outfile file in > and >>
// > outfile can be created and truncated
// >> outfile can be created and appended
// need to check for write permission
int	file_outfile(t_shell *gear_5, t_exec *exec, t_token *token)
{
	if (!exec || !token)
		return (FAILURE);
	if (token->token_type == TOKEN_OUTPUT
		&& token->next->token_type == TOKEN_FILE)
	{
		exec->fd_out = open(token->next->word, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
		write_permission(gear_5, token->next->word);
		if (exec->fd_out < 0)
		{
			perror("Failed to open file for truncation");
			return (FAILURE);
		}
	}
	else if (token->token_type == TOKEN_APPEND
		&& token->next->token_type == TOKEN_FILE)
	{
		exec->fd_out = open(token->next->word, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		write_permission(gear_5, token->next->word);
		if (exec->fd_out < 0)
		{
			perror("Failed to open file for appending");
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
