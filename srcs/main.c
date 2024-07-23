/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/07/23 18:01:35 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list(t_token *head)
{
	t_token	*current;

	current = head;
	if (!current)
		return ;
	while (current)
	{
		printf("Word: %s\n", current->word);
		current = current->next;
	}
}

static int	init_minishell(t_shell *gear_5, t_env *envp)
{
	int		status;
	t_token	*list;

	status = 0;
	list = NULL;
	while (true)
	{
		gear_5->input = readline(RED"Super Gear 5 $> "RESET);
		add_history(gear_5->input);
		if (gear_5->input == NULL)
			break ;
		if (lexing_gear_5(gear_5) == SUCCESS)
			printf(GREEN"Congrats lexing works!\n"RESET);
		else
			printf(BLUE"Check your lexing!\n"RESET);
		free_token_list(list);
		list = NULL;
		extract_words(gear_5->input, &list);
		print_list(list);
	}
	clean_env(envp);
	return (status);
}
//Function to initialize minishell
// • env
// • lexer
// 		→ Delimitor
//		→ Extract word
// • parsing:
//		→ Token
//		→ Order of token
//		→ ...
// • execution

static void	init_structures(t_shell	*gear_5, t_env *envp)
{
	ft_bzero(&gear_5, 1);
	ft_bzero(&envp, 1);
}
//initialize all variables of structures to 0

int	main(int argc, char **argv, char **env)
{
	t_shell	gear_5;
	t_env	envp;
	int		exit_status;

	(void)argv;
	init_structures(&gear_5, &envp);
	init_env(&envp, env);
	exit_status = 0;
	if (argc > 1)
	{
		error("Dont't put arguments\n");
		return (EXIT_FAILURE);
	}
	else
	{
		exit_status = init_minishell(&gear_5, &envp);
	}
	return (exit_status);
}
//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
// faire une fonction error au lieu de mettre ft_putstr_fd a chaque fois ?
