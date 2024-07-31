/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:18 by jewu              #+#    #+#             */
/*   Updated: 2024/07/31 17:25:48 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_double_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
//go to last node of linked list

void	appendright(t_token **head, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (!(*head))
	{
		*head = new;
		new->previous = NULL;
		new->next = NULL;
		return ;
	}
	last = ft_double_lstlast(*head);
	if (last == NULL)
		return ;
	new->previous = last;
	new->next = NULL;
	last->next = new;
}
//add node at the end of the linked list

static void	update_quotes(t_token *new_node, t_parsing *state)
{
	new_node->outer_double_quote = state->outer_double_quote;
	new_node->outer_single_quote = state->outer_single_quote;
}
//update token outer quotes

void	add_to_list(t_token **head, t_parsing *state,
const char *word, int word_length)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		perror("Unable to allocate memory");
		exit(EXIT_FAILURE);
	}
	new_node->word = ft_calloc(word_length + 1, sizeof(char));
	if (!new_node->word)
		return ;
	new_node->outer_double_quote = state->outer_double_quote;
	new_node->outer_single_quote = state->outer_single_quote;
	ft_strncpy(new_node->word, word, word_length);
	appendright(head, new_node);
}
//copy word into char *word of new node and add it to linked list