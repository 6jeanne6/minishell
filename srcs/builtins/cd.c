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

static void go_to_directory(t_shell *gear_5, char *path)
{
    if (chdir(path) == -1)
    {
        error(path);
        error(" : No such file or directory\n");
        gear_5->exit_status = 1;
        return;
    }
    gear_5->exit_status = 0;
}

static void execute_cd(t_shell *gear_5, t_exec *exec)
{
    int i;

    i = 0;
    while (exec->args[i])
        i++;
    if (i > 2)
    {
        error("cd: too many arguments\n");
        gear_5->exit_status = 1;
        return;
    }
    if (i == 1) 
    {
        error("cd: missing arguments\n");
        gear_5->exit_status = 1;
        return;
    }
    else
    {
        go_to_directory(gear_5, exec->args[1]);
    }
}

int cd(t_shell *gear_5, t_env *envp, t_exec *exec)
{
    char *new_path;
    char *last_path;

    if (!envp || !exec || !gear_5)
        return (FAILURE);
    
    execute_cd(gear_5, exec);
    if (gear_5->exit_status == 0)
    {
        new_path = get_current_path();
        last_path = get_env_var_value_with_name(envp, "PWD");
        change_env_var_value_with_name(envp, "OLDPWD", last_path);
        change_env_var_value_with_name(envp, "PWD", new_path);
        free(new_path);
		gear_5->exit_status = 0;
    }
    return (SUCCESS);
}
