/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:56:55 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/20 12:57:13 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_name(char *str)
{
	if (!str || !*str)
		return (0);
	if (ft_strlen(str) == 0)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

//get the current work directory with getcwd (return a string)
char	*get_current_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_putstr_fd("getcwd() Error\n", STDERR_FILENO);
	return (path);
}

int	is_valid_identifier(char *name, t_shell *gear_5, int code)
{
	if (check_var_name(name) == 0)
	{
		if (code == 1)
			error("export: ");
		if (code == 2)
			error("unset: ");
		error(name);
		error(": not a valid identifier");
		ft_putstr_fd("\n", 2);
		free(name);
		gear_5->exit_status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}
