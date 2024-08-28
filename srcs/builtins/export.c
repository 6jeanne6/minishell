/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:02:33 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/24 10:48:11 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    export(t_env *envp)
{
	t_envp *start;

	start = envp;
	while (envp != NULL)
	{
		printf("export ");
		printf("%s =",variable_name);
		printf("%s =",variable_value);
		envp = envp -> next;
	}
}




}
