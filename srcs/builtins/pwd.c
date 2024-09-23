/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:07:52 by jewu              #+#    #+#             */
/*   Updated: 2024/09/23 11:35:07 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//print current working directory
//pwd with no options, arguments ok
int	pwd(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	char	*path;

	(void) envp;
	path = get_current_path();
	ft_putstr_fd(path, exec->fd_out);
	ft_putstr_fd("\n", exec->fd_out);
	free(path);
	gear_5->exit_status = 0;
	return (0);
}
