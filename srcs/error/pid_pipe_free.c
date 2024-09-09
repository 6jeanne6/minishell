/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/09/09 13:32:32 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free pipe tab and pid tab
void	clean_exec(t_exec *exec)
{
	int		i;
	int		nb_cmd;
	t_exec	*current;

	i = -1;
	nb_cmd = exec->nb_cmd;
	if (!exec)
		return ;
	current = exec;
	while (current)
	{
		if (current->pipe_tab)
		{
			while (++i < nb_cmd)
				free(current->pipe_tab[i]);
			free(current->pipe_tab);
		}
		if (current->pid_tab)
			free(current->pid_tab);
		current = current->next;
	}
}