/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:24:09 by jewu              #+#    #+#             */
/*   Updated: 2024/09/05 16:22:02 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//while to put line input in here_doc
static void	gnl_here_doc(t_exec *exec, char *delimiter)
{
	char	*line;

	ft_putstr_fd("heredoc>", 0);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			get_next_line(-42);
			break ;
		}
		ft_putstr_fd(line, exec->fd_in);
		free(line);
		ft_putstr_fd("heredoc>", 0);
		line = get_next_line(0);
	}
	close(exec->fd_in);
}

//handle <<
int	handle_heredoc(t_exec *exec, t_token *token)
{
	char	*delimiter;

	if (!exec || !token)
		return (FAILURE);
	if (token->next)
	{
		delimiter = ft_strjoin(token->next->word, "\n");
		if (!delimiter)
			return (FAILURE);
		exec->fd_in = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (exec->fd_in < 0)
			return (free(delimiter), FAILURE);
		gnl_here_doc(exec, delimiter);
		exec->fd_in = open(".here_doc", O_RDWR, 0644);
		if (exec->fd_in < 0)
			return (free(delimiter), FAILURE);
		close(exec->fd_in);
		unlink(".here_doc");
		free(delimiter);
	}
	return (SUCCESS);
}
