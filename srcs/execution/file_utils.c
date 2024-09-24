/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:21:14 by jewu              #+#    #+#             */
/*   Updated: 2024/09/24 17:25:47 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

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

//handle < : 1st token is command
static int	infile_cmd_execution(t_shell *gear_5, t_token *token)
{
	if (!gear_5 || !token)
		return (FAILURE);
	if (token->previous)
	{
		if (!token->previous->cmd_path
			&& token->previous->token_type != TOKEN_FILE)
		{
			update_exit_status(gear_5, 127, token->previous->word);
			return (FAILURE);
		}
		else if ((access(token->previous->cmd_path, F_OK) == 0)
			&& (access(token->previous->cmd_path, X_OK) == 0))
			return (SUCCESS);
	}
	return (FAILURE);
}

//handle <
static int	handle_input(t_shell *gear_5, t_exec *exec, t_token *token)
{
	if (token->next)
	{
		if ((access(token->next->word, F_OK) == -1)
			|| (access(token->next->word, R_OK) == -1))
		{
			filename_error(token->next->word,
				"no such file or directory", gear_5, 1);
			if (exec->has_pipe == false)
				return (FAILURE);
		}
		exec->fd_in = open(token->next->word, O_RDONLY);
		if (exec->fd_in < 0)
			return (FAILURE);
	}
	return (SUCCESS);
}

//check rights for input file in <
int	file_input(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp)
{
	if (!gear_5 || !exec || !token || !envp)
		return (FAILURE);
	if (exec->fd_in >= 3)
		close(exec->fd_in);
	if (gear_5->j == 0 && token->token_type == TOKEN_INPUT)
	{
		if (infile_cmd_execution(gear_5, token) == FAILURE)
			return (FAILURE);
	}
	else if (token->token_type == TOKEN_INPUT)
	{
		if (handle_input(gear_5, exec, token) == FAILURE)
			return (FAILURE);
	}
	else if (token->token_type == TOKEN_HEREDOC)
	{
		if (create_heredoc(gear_5, exec, token, envp) == FAILURE)
		{
			g_sig_flag = IN_PARENT;
			return (FAILURE);
		}
		g_sig_flag = IN_PARENT;
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
	if (exec->fd_out >= 3)
		close(exec->fd_out);
	if (token->token_type == TOKEN_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (token->token_type == TOKEN_APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (FAILURE);
	exec->fd_out = open(token->next->word, flags, 0644);
	if (access(token->next->word, W_OK) == -1)
		update_exit_status(gear_5, 1, token->next->word);
	if (access(token->next->word, W_OK) == -1)
		update_exit_status(gear_5, 1, token->next->word);
	if (exec->fd_out < 0)
		return (FAILURE);
	return (SUCCESS);
}
