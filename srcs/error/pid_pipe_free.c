/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/09/10 13:16:16 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_gear_5(t_shell *gear_5, t_exec *exec, t_env *envp)
{
	if (!envp || !gear_5)
		return ;
	clean_env(envp);
	clean_exec(exec);
	free_exec(exec);
}

//when execve succeed, clean everything and process can terminate
void	execve_clean_all(t_exec *exec, t_env *envp, t_shell *gear_5)
{
	if (!exec || !envp || !gear_5)
		return ;
	clean_env(envp);
	clean_exec(exec);
	free_exec(exec);
}

//free pipe tab and pid tab
void	clean_exec(t_exec *exec)
{
	t_exec	*current;
	int		i;
	int		nb_cmd;

	if (!exec)
		return ;
	current = exec;
	i = -1;
	nb_cmd = exec->nb_cmd;
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
			while (++i < nb_cmd)
				free(current->pipe_tab[i]);
			free(current->pipe_tab);
		}
		current = current->next;
	}
}
