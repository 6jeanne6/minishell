/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:43:14 by jewu              #+#    #+#             */
/*   Updated: 2024/08/20 23:03:53 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//in t_exec free args
static void	free_args_tab(char **argv)
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

//free each node in token linked list
void	free_token_list(t_token *head)
{
	t_token	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->word);
		free(temp);
		temp = NULL;
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
	if (envp->tmp_path)
	{
		//free(envp->tmp_path);
		envp->tmp_path = NULL;
	}
	if (envp->cmd_path)
	{
		//free(envp->cmd_path);
		envp->cmd_path = NULL;
	}
}
