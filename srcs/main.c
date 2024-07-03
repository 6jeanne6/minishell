/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/07/03 14:57:23 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

static int	init_minishell(t_shell *gear_5, char **env)
{
	while (true)
	{
		(void)env;
		gear_5->input = readline(RED"Super Gear 5 $> "RESET);
		printf("Your input: %s\n", gear_5->input);
	}
	return (g_signal_status);
}
//Function to initialize minishell
// • parsing:
//		→ ...
//		→ ...
//		→ ...
// • execution

int	main(int argc, char **argv, char **env)
{
	t_shell	gear_5;
	int		exit_status;

	(void)argv;
	ft_bzero(&gear_5, 1);
	exit_status = 0;
	if (argc > 1)
	{
		ft_putstr_fd("Don't put arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		exit_status = init_minishell(&gear_5, env);
	return (exit_status);
}
//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
// faire une fonction error au lieu de mettre ft_putstr_fd a chaque fois ?
