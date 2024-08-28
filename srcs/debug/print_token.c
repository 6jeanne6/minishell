/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:16:25 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/27 18:40:16 by lnjoh-tc         ###   ########.fr       */
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

#include <stdio.h>
#include <unistd.h> // Pour pid_t

void print_exec_list(t_exec *exec)
{
    t_exec *current = exec;

    while (current != NULL)
    {
        // Affiche l'ID de l'exécution
        printf("ID: %d\n", current->id);

        // Affiche les PID dans pid_tab
        if (current->pid_tab)
        {
            printf("PID Tab: ");
            for (int i = 0; current->pid_tab[i] != -1; i++) // On suppose que -1 termine pid_tab
                printf("%d ", current->pid_tab[i]);
            printf("\n");
        }

        // Affiche les flags de citation
        printf("In Double Quote: %d\n", current->in_double_quote);
        printf("Outer Double Quote: %d\n", current->outer_double_quote);
        printf("Outer Single Quote: %d\n", current->outer_single_quote);

        // Affiche les descripteurs de fichier
        printf("FD In: %d\n", current->fd_in);
        printf("FD Out: %d\n", current->fd_out);

        // Affiche les pipes
        if (current->pipe_tab)
        {
            printf("Pipe Tab:\n");
            for (int i = 0; current->pipe_tab[i] != NULL; i++)
            {
                printf("  Pipe %d: [%d, %d]\n", i, current->pipe_tab[i][0], current->pipe_tab[i][1]);
            }
        }

        // Affiche le nom de la commande et le chemin binaire
        printf("Command Name: %s\n", current->cmd_name ? current->cmd_name : "NULL");
        printf("Binary Path: %s\n", current->bin ? current->bin : "NULL");

        // Affiche les arguments
        if (current->args)
        {
            printf("Arguments: ");
            for (int i = 0; current->args[i] != NULL; i++)
                printf("%s ", current->args[i]);
            printf("\n");
        }

        // Passe à l'élément suivant de la liste
        current = current->next;

        // Ajoute une ligne vide pour séparer les éléments
        printf("\n");
    }
}
