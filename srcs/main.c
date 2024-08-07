/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/08/07 18:28:21 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token, int index)
{
	if (token == NULL)
	{
		printf("Token %d: NULL\n", index);
		return ;
	}

    // Afficher le numéro du token
	printf("Token %d:\n", index);
	printf("  Word: %s\n", token->word);
	printf("  Token Type: ");
	if (token->token_type == TOKEN_CMD)
		printf("COMMAND\n");
	else if (token->token_type == TOKEN_ARG)
		printf("ARGUMENT\n");
	else if (token->token_type == TOKEN_PIPE)
		printf("PIPE\n");
	else if (token->token_type == TOKEN_INPUT)
		printf("INPUT REDIRECTION\n");
	else if (token->token_type == TOKEN_OUTPUT)
		printf("OUTPUT REDIRECTION\n");
	else if (token->token_type == TOKEN_APPEND)
		printf("OUTPUT APPEND\n");
	else if (token->token_type == TOKEN_HEREDOC)
		printf("HEREDOC\n");
	else if (token->token_type == TOKEN_VARIABLE)
		printf("VARIABLE\n");
	else if (token->token_type == TOKEN_FILE)
		printf("FILE\n");
	else if (token->token_type == TOKEN_BUILTIN)
		printf("BUILTIN\n");
	else if (token->token_type == TOKEN_VARIABLEASSIGNATION)
		printf("VARIABLE ASSIGNATION\n");
	else
		printf("UNKNOWN\n");
    // Afficher les doubles quotes extérieures
	printf("  Outer Double Quote: %d\n", token->outer_double_quote);
	printf("  Outer Single Quote: %d\n", token->outer_single_quote);
}

void	print_token_list(t_token *list)
{
	int		index;
	t_token	*current;

	index = 0;
	current = list;
	while (current != NULL)
	{
		print_token(current, index);
		current = current->next;
		index++;
	}
}

static void	parse_gear_5(t_shell *gear_5, t_env *envp, t_token *list)
{
	lexing_gear_5(gear_5);
	free_token_list(list);
	list = NULL;
	extract_words(gear_5->input, &list);
	get_token_type(envp, list);
	token_order(envp, list, gear_5);
	print_token_list(list);
	expander(list, envp);
	free_token_list(list);
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
		gear_5->input = readline(RED"Super Gear 5 $> "RESET);
		add_history(gear_5->input);
		if (gear_5->input == NULL)
			break ;
		parse_gear_5(gear_5, envp, list);
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
