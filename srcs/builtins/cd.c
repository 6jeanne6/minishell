/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:08:04 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/24 09:29:44 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_env *envp)
{
	char	*path = NULL;
	char	*new_path;
	char	*last_path;

	if (chdir(path) == -1)
	{
		ft_printf("%s: No such file or directory\n", path);
		return (FAILURE);
	}
	last_path = envp->pwd;
	new_path = get_current_path();
	envp->pwd = new_path;
	envp->oldpwd = last_path;
	return (SUCCESS);
}
// Lui donnée l'argument 