/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:36:25 by jewu              #+#    #+#             */
/*   Updated: 2024/09/09 19:15:16 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_gear_5(t_shell *gear_5, t_exec *exec, t_env *envp)
{
	int	i;
	int	nb_cmd;

	i = -1;
	if (!exec || !envp || !gear_5)
		return ;
	nb_cmd = exec->nb_cmd;
	// if (gear_5->pipe_tab)
	// {
	// 	while (++i < nb_cmd)
	// 		free(gear_5->pipe_tab[i]);
	// 	free(gear_5->pipe_tab);
	// }
	clean_env(envp);
	clean_exec(exec, gear_5);
	free_exec(exec);
}

//when execve succeed, clean everything and process can terminate
void	execve_clean_all(t_exec *exec, t_env *envp, t_shell *gear_5)
{
	if (!exec || !envp || gear_5)
		return ;
	clean_env(envp);
	clean_exec(exec, gear_5);
	free_exec(exec);
}

//free pipe tab and pid tab
void	clean_exec(t_exec *exec, t_shell *gear_5)
{
	t_exec	*current;

	if (!exec)
		return ;
	(void)gear_5;
	current = exec;
	while (current)
	{
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->pid_tab)
			free(current->pid_tab);
		if (current->bin)
			free(current->bin);
		current = current->next;
	}
}
