/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:40:22 by jewu              #+#    #+#             */
/*   Updated: 2024/07/07 21:11:15 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_path(t_env *envp)
{
	if (!envp->env[0])
	{
		//search PATH in /etc/environment
		;
	}
	else
	{
		find_path(envp);
	}
}
//init minishell to copy PATH

char	**file_to_struct(t_env *envp)
{
	int	fd;
	char *line = NULL;

	// Open the file
	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Could not open the file\n", STDERR_FILENO);
		return (NULL);
	}
	// Extract the line from the file 
	line = get_next_line(fd);
	if (line == NULL)
	{
		close (fd);
		return (NULL);
	}
	// Close the FD
	close(fd);
	
	//Allocate memory
	envp->env = (char **)malloc(sizeof(char *));
    if (envp->env == NULL) 
	{
        free(line);
        return (NULL);
    }
	// Copy line
	envp->env[0] = strdup(line);
	if (envp->env[0] == NULL) 
	{
        free(line);     
        free(envp->env);
        envp->env = NULL;
        return (NULL);
    }
	
	// Free line
	free(line);
}
