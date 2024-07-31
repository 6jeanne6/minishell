/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/07/31 18:33:15 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_token(t_token *token, int index) {
    if (token == NULL) {
        printf("Token %d: NULL\n", index);
        return;
    }

    // Afficher le numéro du token
    printf("Token %d:\n", index);
    printf("  Word: %s\n", token->word);
    printf("  Token Type: ");
    if (token->token_type == TOKEN_CMD) {
        printf("COMMAND\n");
    } else if (token->token_type == TOKEN_ARG) {
        printf("ARGUMENT\n");
    } else if (token->token_type == TOKEN_PIPE) {
        printf("PIPE\n");
    } else if (token->token_type == TOKEN_INPUT) {
        printf("INPUT REDIRECTION\n");
    } else if (token->token_type == TOKEN_OUTPUT) {
        printf("OUTPUT REDIRECTION\n");
    } else if (token->token_type == TOKEN_APPEND) {
        printf("OUTPUT APPEND\n");
    } else if (token->token_type == TOKEN_HEREDOC) {
        printf("HEREDOC\n");
    } else if (token->token_type == TOKEN_VARIABLE) {
        printf("VARIABLE\n");
    } else if (token->token_type == TOKEN_FILE) {
        printf("FILE\n");
    } else if (token->token_type == TOKEN_BUILTIN) {
        printf("BUILTIN\n");
    } else if (token->token_type == TOKEN_VARIABLEASSIGNATION) {
        printf("VARIABLE ASSIGNATION\n");
    } else {
        printf("UNKNOWN\n");
    }

    // Afficher les doubles quotes extérieures
    printf("  Outer Double Quote: %d\n", token->outer_double_quote);
    printf("  Outer Single Quote: %d\n", token->outer_single_quote);
}

void print_token_list(t_token *list) {
    int index = 0;
    t_token *current = list;
    while (current != NULL) {
        print_token(current, index);
        current = current->next;
        index++;
    }
}

static int init_minishell(t_shell *gear_5, t_env *envp)
{
    int         status;
    t_token     *list;

    status = 0;
    list = NULL;

    gear_5->input = readline("Input : " RESET);
    add_history(gear_5->input);
    if (gear_5->input != NULL)
    {
        lexing_gear_5(gear_5);
        free_token_list(list); // Assurez-vous que cette fonction ne libère pas la liste avant d'avoir extrait les nouveaux tokens
        list = NULL;
        extract_words(gear_5->input, &list);
        get_token_type(envp, list);
        print_token_list(list); 
        free_token_list(list); // Imprimez la liste des tokens ici pour le débogage
    }
    clean_env(envp);
    return (status);
}
//Function to initialize minishell
// • env
// • lexer
// 		→ Delimitor
// • parsing:
//		→ Extract words
//		→ Add to linked list
//		→ Tokenizer
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
	int			exit_status;

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
		exit_status = init_minishell(&gear_5, &envp);
	return (exit_status);
}
//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
// faire une fonction error au lieu de mettre ft_putstr_fd a chaque fois ?
