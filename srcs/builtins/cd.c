/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:08:04 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/23 15:02:08 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change directory with chdir
static void	go_to_directory(t_shell *gear_5, char *path, t_env *env)
{
	(void)env;
	if (ft_strcmp(path, "-") == 0 || ft_strcmp(path, "~") == 0)
	{
		error(path);
		error(" : is not a relative or absolute path\n");
		gear_5->exit_status = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		error(path);
		error(" : No such file or directory\n");
		gear_5->exit_status = 1;
		return ;
	}
	gear_5->exit_status = 0;
}

// how many arguments after cd
static void	execute_cd(t_shell *gear_5, t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
	while (exec->args[i])
		i++;
	if (i > 2)
	{
		error("cd: too many arguments\n");
		gear_5->exit_status = 1;
		return ;
	}
	if (i == 1)
	{
		error("cd: missing relative or absolute path\n");
		gear_5->exit_status = 1;
		return ;
	}
	else
		go_to_directory(gear_5, exec->args[1], env);
}

//change directory
//after execute cd we update pwd with new and last path
//create an OLDPWD, update its path
//update PWD with newest path
int	cd(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	char	*new_path;
	char	*last_path;

	if (!envp || !exec || !gear_5)
		return (FAILURE);
	execute_cd(gear_5, exec, envp);
	if (gear_5->exit_status == 0)
	{
		new_path = get_current_path();
		if (!new_path)
			return (FAILURE);
		last_path = get_env_var_value_with_name(envp, "PWD");
		change_env_var_value_with_name(envp, "OLDPWD", last_path);
		change_env_var_value_with_name(envp, "PWD", new_path);
		free(new_path);
		gear_5->exit_status = 0;
	}
	return (SUCCESS);
}
