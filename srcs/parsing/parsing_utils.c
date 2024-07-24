/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:18 by jewu              #+#    #+#             */
/*   Updated: 2024/07/24 17:43:32 by jewu             ###   ########.fr       */
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

void	add_to_list(t_token **head, const char *word, int word_length)
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
	ft_strncpy(new_node->word, word, word_length);
	appendright(head, new_node);
}
//copy word into char *word of new node and add it to linked list