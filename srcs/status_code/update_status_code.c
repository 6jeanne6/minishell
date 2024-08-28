/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:41:43 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/28 16:22:22 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar_question_mark_input(t_shell *gear_5)
{
	if (ft_strcmp(gear_5->input, "$?") == 0)
	{
		printf("%d\n", gear_5->exit_status);
		return (SUCCESS);
	}
	return (FAILURE);
}
int	update_exit_status_code(t_shell *gear_5)
{
	if (is_dollar_question_mark_input(gear_5) == SUCCESS)
		return(SUCCESS);
	else
		gear_5->exit_status = 0;
	return(FAILURE);
}
