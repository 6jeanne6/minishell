/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/08/22 19:44:44 by jewu             ###   ########.fr       */
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

//proceed to execution of Super_Gear_5 shell
// • execution:
//		→ pid
//		→ fork
//		→ waitpid
//		→ close fds and pipes

// static int cleanup_parse(t_token **list, t_exec **exec)
// {
// 	free_token_list(*list);
// 	free_exec(*exec);
// 	*list = NULL;
// 	*exec = NULL;
// 	return (FAILURE);
// }

static int	execute_gear_5(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!gear_5 || !envp || !exec)
		return (FAILURE);
	if (exec->bin)
	{
		execve(exec->bin, exec->args, envp->env);
		if (execve(exec->bin, exec->args, envp->env) < 0)
		{
			gear_5->exit_status = 1;
			error("Check your execve\n");
			return (FAILURE);
		}
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

//if first token
static int	process_builtin(t_shell *gear_5, t_env *envp, t_token *list)
{
	if (list->token_type == TOKEN_BUILTIN)
	{
		if (builtin_order(gear_5, list, envp) == FAILURE)
		{
			free_token_list(list);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	parse_gear_5(t_shell *gear_5, t_env *envp, t_token *list,
t_exec **exec)
{
	if (lexing_gear_5(gear_5) == SUCCESS)
	{
		free_token_list(list);
		list = NULL;
		extract_words(gear_5->input, &list);
		if (!list)
			return (FAILURE);
		get_token_type(envp, list);
		if (token_order(list, gear_5) == FAILURE)
			return (wrong_token_order(list, envp), FAILURE);
		print_token_list(list);
		if (process_builtin(gear_5, envp, list) == FAILURE)
			return (FAILURE);
		expander(list, envp);
		*exec = init_exec(gear_5, list, envp);
		if (!*exec)
		{
			printf("lol no t_exec\n");
			free_t_exec(list, envp);
			return (FAILURE);
		}
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
//		→ Token order
//		→ Init t_exec structure with tab **args and redirections

static int	init_minishell(t_shell *gear_5, t_env *envp)
{
	t_token	*list;
	t_exec	*exec;

	list = NULL;
	exec = NULL;
	while (true)
	{
		free_exec(exec);
		exec = NULL;
		gear_5->input = readline(RED"Super Gear 5 $> "RESET);
		add_history(gear_5->input);
		if (gear_5->input == NULL)
			break ;
		if (parse_gear_5(gear_5, envp, list, &exec) == FAILURE)
			continue ;
		if (execute_gear_5(gear_5, envp, exec) == FAILURE)
			continue ;
	}
	clean_env(envp);
	free_exec(exec);
	return (gear_5->exit_status);
}
//Function to initialize minishell
// • env
// • lexer
// • parsing
// • execution

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
	ft_bzero(&gear_5, sizeof(t_shell));
	ft_bzero(&envp, sizeof(t_env));
	init_env(&envp, env);
	gear_5.exit_status = init_minishell(&gear_5, &envp);
	return (gear_5.exit_status);
}
//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
// faire une fonction error au lieu de mettre ft_putstr_fd a chaque fois ?
