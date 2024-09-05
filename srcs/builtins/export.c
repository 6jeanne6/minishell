/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:02:33 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/05 14:33:33 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_env *envp)
{
	t_env	*start;

	start = envp;
	while (envp != NULL)
	{
		printf("export ");
		printf("%s =",variable_name);
		printf("%s =",variable_value);
		envp = envp->next;
	}
}
