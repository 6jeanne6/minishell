/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:08:04 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/07/17 13:48:57 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

Utiliser les DEFINE FAILURE ET SUCCES

int	cd(t_env *envp)
{
	char	*path;
	char	*new_path;
	char	*last_path;

	if (chdir(path) == -1)
	{
		ft_printf("%s: No such file or directory\n", path);
		return (FAILURE);
	}
	last_path = envp->PATH;
	new_path = get_current_path();
	envp->PATH = new_path;
	envp->OLDPWD = last_path;
	return (SUCCESS);
}
*/