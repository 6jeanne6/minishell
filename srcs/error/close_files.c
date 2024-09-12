/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:37:20 by jewu              #+#    #+#             */
/*   Updated: 2024/09/12 14:54:25 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//close all files
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
		current = current->next;
	}
}
