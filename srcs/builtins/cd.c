/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:08:04 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/05 14:28:07 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_env *envp, t_exec *exec, t_shell *gear_5)
{
	char	*path;
	char	*new_path;
	char	*last_path;

	if (!envp || !exec || !gear_5)
		return (FAILURE);
	path = exec->cmd_name;
	if (chdir(path) == -1)
	{
		error(path);
		error(": No such file or directory\n");
		update_exit_status(gear_5, 1, NULL);
		return (gear_5->exit_status);
	}
	last_path = envp->pwd;
	new_path = get_current_path();
	envp->pwd = new_path;
	envp->oldpwd = last_path;
	return (SUCCESS);
}
