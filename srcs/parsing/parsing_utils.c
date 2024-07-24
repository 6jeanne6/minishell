/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:46:18 by jewu              #+#    #+#             */
/*   Updated: 2024/07/23 17:48:34 by jewu             ###   ########.fr       */
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

void	appendright(t_token **head, t_token *new)
{
	t_token	*last;

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

void	add_to_list(t_token **head, const char *word)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	{
		perror("Unable to allocate memory");
		exit(EXIT_FAILURE);
	}
	strncpy(new_node->word, word, MAX_WORD_LENGTH);
	new_node->word[MAX_WORD_LENGTH - 1] = '\0';
	appendright(head, new_node);
}
