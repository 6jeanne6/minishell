/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:43:14 by jewu              #+#    #+#             */
/*   Updated: 2024/09/18 12:44:47 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//in t_exec free args
void	free_args_tab(char **argv)
{
	int	i;

	i = -1;
	if (!argv)
		return ;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

void	free_exec(t_exec *exec)
{
	t_exec	*tmp;

	if (!exec)
		return ;
	while (exec)
	{
		tmp = exec->next;
		free_args_tab(exec->args);
		free(exec);
		exec = tmp;
	}
}

//customized message
void	error(char	*message)
{
	if (!message)
		return ;
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

//free tmp path and cmd path
void	free_envp_path(t_env *envp)
{
	if (!envp)
		return ;
	if (envp->cmd_path)
	{
		free(envp->cmd_path);
		envp->cmd_path = NULL;
	}
}

//free envp structure
void	clean_env(t_env *envp)
{
	int	i;

	i = 0;
	if (!envp->env[0])
	{
		free(envp->env_tmp[i]);
		free(envp->env_tmp);
	}
	i = 0;
	if (envp->path)
	{
		while (envp->path[i])
		{
			free(envp->path[i]);
			i++;
		}
		free(envp->path);
	}
	free_var_list(envp);
	free(envp->pwd);
	if (envp->oldpwd)
		free(envp->oldpwd);
	free_envp_path(envp);
}
