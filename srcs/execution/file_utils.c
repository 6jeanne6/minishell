/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:21:14 by jewu              #+#    #+#             */
/*   Updated: 2024/09/13 16:31:53 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check if fd is STDIN, STDOUT or STDERR or not
bool	basic_fd(t_exec *exec)
{
	if (!exec)
		return (false);
	if (exec->fd_in > 2 || exec->fd_out > 2)
		return (false);
	else
		return (true);
}

//check if we can write into the file
static void	write_permission(t_shell *gear_5, char *file)
{
	if (!gear_5 || !file)
		return ;
	if (access(file, W_OK) == -1)
		update_exit_status(gear_5, 1, file);
}

//handle <
static int	handle_input(t_shell *gear_5, t_exec *exec, t_token *token)
{
	if (token->next)
	{
		if ((access(token->next->word, F_OK) == -1)
			|| (access(token->next->word, R_OK) == -1))
		{
			filename_error(token->next->word, "unknown file", gear_5, 1);
			return (FAILURE);
		}
		exec->fd_in = open(token->next->word, O_RDONLY);
		if (exec->fd_in < 0)
			return (FAILURE);
	}
	if (token->previous)
	{
		if (!token->previous->cmd_path)
		{
			update_exit_status(gear_5, 127, token->previous->word);
			return (FAILURE);
		}
		else if ((access(token->previous->cmd_path, F_OK) == 0)
			&& (access(token->previous->cmd_path, X_OK) == 0))
			return (SUCCESS);
	}
	return (SUCCESS);
}

//check rights for input file in <
int	file_input(t_shell *gear_5, t_exec *exec, t_token *token)
{
	if (!gear_5 || !exec || !token)
		return (FAILURE);
	if (token->token_type == TOKEN_INPUT)
	{
		if (handle_input(gear_5, exec, token) == FAILURE)
			return (FAILURE);
	}
	else if (token->token_type == TOKEN_HEREDOC)
	{
		if (create_heredoc(exec, token) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

//check rights for outfile file in > and >>
// > outfile can be created and truncated
// >> outfile can be created and appended
// need to check for write permission
int	file_outfile(t_shell *gear_5, t_exec *exec, t_token *token)
{
	int	flags;

	if (!exec || !token || token->next->token_type != TOKEN_FILE)
		return (FAILURE);
	if (token->token_type == TOKEN_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (token->token_type == TOKEN_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (FAILURE);
	exec->fd_out = open(token->next->word, flags, 0644);
	write_permission(gear_5, token->next->word);
	if (exec->fd_out < 0)
		return (FAILURE);
	return (SUCCESS);
}
