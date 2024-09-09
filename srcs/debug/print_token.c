/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:16:25 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/05 12:32:50 by jewu             ###   ########.fr       */
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

void	print_exec_list(t_exec *exec)
{
	t_exec	*current;

	current = exec;
	if (!current)
		return ;
	while (current != NULL)
	{
		printf("ID: %d\n", current->id);
		if (current->pid_tab)
		{
			printf("PID Tab: ");
			for (int i = 0; current->pid_tab[i] != -1; i++) // On suppose que -1 termine pid_tab
				printf("%d ", current->pid_tab[i]);
			printf("\n");
		}
		printf("In Double Quote: %d\n", current->in_double_quote);
		printf("Outer Double Quote: %d\n", current->outer_double_quote);
		printf("Outer Single Quote: %d\n", current->outer_single_quote);
		printf("FD In: %d\n", current->fd_in);
		printf("FD Out: %d\n", current->fd_out);
		if (current->pipe_tab)
		{
			printf("Pipe Tab:\n");
			for (int i = 0; current->pipe_tab[i] != NULL; i++)
				printf("  Pipe %d: [%d, %d]\n", i, current->pipe_tab[i][0], current->pipe_tab[i][1]);
		}
		printf("Command Name: %s\n", current->cmd_name ? current->cmd_name : "NULL");
		printf("Binary Path: %s\n", current->bin ? current->bin : "NULL");
		if (current->args)
		{
			printf("Arguments: ");
			for (int i = 0; current->args[i] != NULL; i++)
				printf("%s ", current->args[i]);
			printf("\n");
		}
		current = current->next;
		printf("\n");
	}
}