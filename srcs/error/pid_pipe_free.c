/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/09/10 18:33:38 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//when execve succeed, clean everything and process can terminate
void	execve_clean_all(t_exec *exec, t_env *envp, t_shell *gear_5)
{
	if (!envp || !gear_5)
		return ;
	clean_env(envp);
	clean_exec(exec);
	free_exec(exec);
}

//free stuff in t_exec
void	clean_exec(t_exec *exec)
{
	t_exec	*current;
	int		i;

	if (!exec)
		return ;
	current = exec;
	i = -1;
	while (current)
	{
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->pid_tab)
			free(current->pid_tab);
		if (current->bin)
			free(current->bin);
		if (current->pipe_tab)
		{
			while (++i < current->nb_cmd - 1)
				free(current->pipe_tab[i]);
			free(current->pipe_tab);
		}
		current = current->next;
	}
}
