/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:49:19 by jewu              #+#    #+#             */
/*   Updated: 2024/10/16 18:33:38 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//clean previous exec when current exec has failed
void	init_exec_clean(t_exec *exec)
{
	t_exec	*tmp;

	if (!exec)
		return ;
	while (exec)
	{
		tmp = exec;
		exec = exec->next;
		close_redir_fd(tmp);
		fail_set_fd_clean(tmp);
	}
}

//close redir fd when >= than 3
void	set_fd_has_failed(t_exec *exec, t_shell *gear_5)
{
	if (!exec || !gear_5)
		return ;
	if (exec->has_pipe == false)
		fail_set_fd_clean(exec);
	else if (exec->heredoc_here == true)
		fail_set_fd_clean(exec);
}

//close redir fd when >= than 3
void	close_redir_fd(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->fd_in >= 3)
		close(exec->fd_in);
	if (exec->fd_out >= 3)
		close(exec->fd_out);
}
