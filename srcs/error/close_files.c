/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:37:20 by jewu              #+#    #+#             */
/*   Updated: 2024/09/16 18:45:44 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//close all files when input is incorrect
void	error_close_files(t_exec *exec)
{
	t_exec	*current;

	if (!exec)
		return ;
	current = exec;
	while (current)
	{
		if (current->fd_in >= 3)
			close(current->fd_in);
		else if (current->fd_in >= 0)
			close(current->fd_in);
		if (current->fd_out >= 3)
			close(current->fd_out);
		else if (current->fd_out >= 0)
			close(current->fd_out);
		if (current->heredoc_here == true)
			unlink(current->heredoc_file);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		current = current->next;
	}
}

//close all files when input is working
void	close_files(t_exec *exec)
{
	t_exec	*current;

	if (!exec)
		return ;
	current = exec;
	while (current)
	{
		if (current->fd_in >= 3)
			close(current->fd_in);
		if (current->fd_out >= 3)
			close(current->fd_out);
		if (current->heredoc_here == true)
		{
			close(current->fd_in);
			unlink(current->heredoc_file);
		}
		current = current->next;
	}
}
