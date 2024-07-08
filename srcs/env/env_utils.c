/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:24:03 by jewu              #+#    #+#             */
/*   Updated: 2024/07/08 17:02:33 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	alloc_fetch(t_env *envp, char *line)
{
	if (!line || !envp)
		return ;
	envp->env = (char **)malloc(sizeof(char *));
	if (!envp->env)
	{
		free(line);
		return ;
	}
	envp->env[0] = ft_strdup(line);
	if (!envp->env[0])
	{
		free(line);
		free(envp->env);
		envp->env = NULL;
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
}
//fetch path for empty env in etc/environment

char	**split_path(t_env *envp, char *str)
{
	char	**ptr;

	ptr = ft_split(str, ':');
	if (!ptr)
		clean_env(envp);
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
