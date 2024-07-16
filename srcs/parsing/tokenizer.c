/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:18 by jewu              #+#    #+#             */
/*   Updated: 2024/07/16 22:58:11 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(t_shell *gear_5, t_env *envp)
{
	int		i;
	t_token	tokenizer;

	i = -1;
	(void)envp;
	ft_bzero(&tokenizer, 1);
	if (!gear_5)
		error("Empty gear_5\n");
	while (gear_5->input[++i])
	{
		if ((i_am_delimitor(gear_5->input)) == true)
		{
		
		}
	}
	return (SUCCESS);
}
//function to classify tokens