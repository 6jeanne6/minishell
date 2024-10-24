/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tool3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:59:55 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/23 14:37:35 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Check if the arguemnt is a numeric*/
int	check_if_arg_is_a_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/* Free tmp var in export */
void	free_env_vars(t_var *head)
{
	t_var	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->variable_name);
		free(temp->variable_value);
		free(temp);
	}
}
