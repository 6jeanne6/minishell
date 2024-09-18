/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:24:03 by jewu              #+#    #+#             */
/*   Updated: 2024/09/18 18:59:35 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	alloc_fetch(t_env *envp, char *line)
{
	if (!line || !envp)
		return ;
	envp->env_tmp = (char **)malloc(sizeof(char *));
	if (!envp->env_tmp)
	{
		free(line);
		return ;
	}
	envp->env_tmp[0] = ft_strdup(line);
	if (!envp->env_tmp[0])
	{
		free(line);
		free(envp->env_tmp);
		envp->env_tmp = NULL;
	}
	free(line);
}
//alloc memory for empty env which contains PATH and copy it

void	fetch_path(t_env *envp)
{
	int		fd;
	char	*line;

	fd = open("/etc/environment", O_RDONLY);
	line = NULL;
	if (fd == -1)
	{
		ft_putstr_fd("Could not open the file\n", STDERR_FILENO);
		return ;
	}
	line = get_next_line(fd);
	if (line == NULL)
	{
		close (fd);
		return ;
	}
	close(fd);
	alloc_fetch(envp, line);
	get_next_line(-42);
}
//fetch path for empty env in etc/environment

char	**split_path(t_env *envp, char *str)
{
	char	**ptr;

	(void)envp;
	ptr = ft_split(str, ':');
	if (!ptr)
		return (NULL);
	return (ptr);
}
//split the PATH into sub_paths

char	**find_path(t_env *envp, char **path)
{
	int	i;

	i = 0;
	if (!envp || !envp->env)
		ft_putstr_fd("No environment!\n", 2);
	while (envp->env[i] && (ft_strnstr(envp->env[i], "PATH=", 5) == 0))
		i++;
	path = split_path(envp, envp->env[i]);
	return (path);
}
//check the PATH

char	**copy_path(t_env *envp)
{
	char	**search_path;

	search_path = NULL;
	if (!envp->env[0])
	{
		fetch_path(envp);
		search_path = split_path(envp, envp->env_tmp[0]);
	}
	else
		search_path = find_path(envp, search_path);
	return (search_path);
}
//env is NULL or not? fetch path