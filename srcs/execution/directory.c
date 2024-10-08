/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:25:49 by jewu              #+#    #+#             */
/*   Updated: 2024/10/07 15:45:52 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check if argument is a directory
//directory alone cannot be executed
//give ./ for 126
int	is_dir(char *path, t_shell *gear_5)
{
	DIR	*dir;

	if (!path)
		return (FAILURE);
	if (ft_strchr(path, '/') == 0)
		return (FAILURE);
	dir = opendir(path);
	if (dir == NULL)
		return (FAILURE);
	closedir(dir);
	error(path);
	error(" : Is a directory\n");
	gear_5->exit_status = 126;
	return (SUCCESS);
}