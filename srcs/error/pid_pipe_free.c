/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/09/08 16:01:21 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free pipe tab and pid tab
void	clean_exec(t_exec *exec)
{
	int	i;
	int	nb_cmd;

	i = -1;
	nb_cmd = exec->nb_cmd;
	if (!exec)
		return ;
	if (exec->pipe_tab)
	{
		while (++i < nb_cmd)
			free(exec->pipe_tab[i]);
		free(exec->pipe_tab);
	}
	if (exec->pid_tab)
		free(exec->pid_tab);
}
