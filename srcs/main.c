/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/08/23 15:32:44 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_gear_5(t_shell *gear_5, t_env *envp, t_token *list)
{
	if (lexing_gear_5(gear_5) == SUCCESS)
	{
		free_token_list(list);
		list = NULL;
		extract_words(gear_5->input, &list);
		get_token_type(envp, list);
		token_order(envp, list, gear_5);
		if (list->token_type == TOKEN_BUILTIN)
		{
			if (builtin_order(gear_5, list, envp) == FAILURE)
			{
				free_token_list(list);
				return (FAILURE);
			}
		}
		expander(list, envp);
		free_token_list(list);
		return (SUCCESS);
	}
	return (FAILURE);
}

//• lexer
// 		→ Delimitor
// • parsing:
//		→ Extract words
//		→ Add to linked list
//		→ Tokenizer
static int	init_minishell(t_shell *gear_5, t_env *envp)
{
	t_token	*list;

	list = NULL;
	while (true)
	{
		gear_5->input = readline("Super Gear 5 $> ");
		add_history(gear_5->input);
		if (gear_5->input == NULL)
			break ;
		if (parse_gear_5(gear_5, envp, list) == FAILURE)
			continue ;
	}
	clean_env(envp);
	return (gear_5->exit_status);
}

//Function to initialize minishell
// • env
// • lexer
// • parsing
// • execution
static void	init_structures(t_shell	*gear_5, t_env *envp)
{
	ft_bzero(gear_5, sizeof(t_shell));
	ft_bzero(envp, sizeof(t_env));
}

//initialize all variables of structures to 0
int	main(int argc, char **argv, char **env)
{
	t_shell		gear_5;
	t_env		envp;

	(void)argv;
	if (argc > 1)
	{
		error("Dont't put arguments\n");
		return (EXIT_FAILURE);
	}
	init_structures(&gear_5, &envp);
	init_env(&envp, env);
	gear_5.exit_status = init_minishell(&gear_5, &envp);
	return (gear_5.exit_status);
}
//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
// faire une fonction error au lieu de mettre ft_putstr_fd a chaque fois ?
