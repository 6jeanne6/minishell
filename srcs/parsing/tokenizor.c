/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:18 by jewu              #+#    #+#             */
/*   Updated: 2024/07/17 21:53:03 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool delimitor_except_blank(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z') || (c == '|') || (c == '\'') || (c == '"')
			|| (c == '|') || (c == '>') || (c == '<'))
		return (true);
	else
		return (false);
}
//delimitors except blanks: pipe, chevrons, quotes
//to avoid putting each blank into a node

static void print_token_list(t_token *token_list)
{
    t_token *current = token_list;
    while (current)
	{
        printf("Token: %s\n", current->content);
        current = current->next;
    }
}

static t_token	*ft_double_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
//checks if we are in the last node of a linked chain

static void	appendright(t_token **token_list, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (!(*token_list))
	{
		*token_list = new;
		return ;
	}
	ft_bzero(last, 1);
	last = ft_double_lstlast(*token_list);
	if (last == NULL)
		return ;
	ft_bzero(new, 1);
	new->previous = last;
	new->next = NULL;
	last->next = new;
}
//adds a node in the double linked list at the back

static t_token	*new_node(char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	ft_bzero(new, 1);
	new->content = content;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
//creates a new node

static t_token *extract_content(char *input, int start, int end)
{
	int		i;
	char	*content;
	t_token	*token_list;
	t_token	*tmp;

	i = start;
	content = ft_calloc(end - start + 1, 1);
	if (!content)
		return (NULL);
	while (input[i] && i <= end)
	{
		{
			content[i] = input[i];
			i++;
		}
	}
	content[i] = '\0';
	tmp = new_node(content);
	if (!tmp)
		return (NULL);
	appendright(&token_list, tmp);
	return (token_list);
}
//extract the content to add in a linked list node

int tokenizor(t_shell *gear_5, t_env *envp)
{
	int		i;
	int		start;
	bool	blank;
	t_token	*token;

	i = -1;
	start = 0;
	blank = true;
	(void)envp;
	if (!gear_5)
		error("Empty gear_5\n");
	while (gear_5->input[++i])
	{
		if ((delimitor_except_blank(gear_5->input[i]) == true) && (blank == true))
		{
			blank = false;
			start = i;
		}
		if (((i_am_delimitor(gear_5->input[i])) == true) && (blank == false))
		{
			token = extract_content(gear_5->input, start, i);
			if (!token)
				return (FAILURE);
			blank = true;
		}	
	}
	print_token_list(token);
	return (SUCCESS);
}
//function to classify tokens