/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:18 by jewu              #+#    #+#             */
/*   Updated: 2024/07/18 19:00:03 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_token	*ft_double_lstlast(t_token *lst)
// {
// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }
// //checks if we are in the last node of a linked chain

// static void	appendright(t_token **token_list, t_token *new)
// {
// 	t_token	*last;

// 	last = NULL;
// 	if (!(*token_list))
// 	{
// 		*token_list = new;
// 		return ;
// 	}
// 	ft_bzero(last, 1);
// 	last = ft_double_lstlast(*token_list);
// 	if (last == NULL)
// 		return ;
// 	ft_bzero(new, 1);
// 	new->previous = last;
// 	new->next = NULL;
// 	last->next = new;
// }
// //adds a node in the double linked list at the back

// static t_token	*new_node(char *content)
// {
// 	t_token	*new;

// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	ft_bzero(new, 1);
// 	new->content = content;
// 	new->previous = NULL;
// 	new->next = NULL;
// 	return (new);
// }
// //creates a new node

// static t_token	*extract_content(char *input, int start, int end)
// {
// 	int		i;
// 	char	*content;
// 	t_token	*token_list;
// 	t_token	*tmp;

// 	i = start;
// 	content = ft_calloc(end - start + 1, 1);
// 	if (!content)
// 		return (NULL);
// 	while (input[i] && i <= end)
// 	{
// 		{
// 			content[i] = input[i];
// 			i++;
// 		}
// 	}
// 	content[i] = '\0';
// 	tmp = new_node(content);
// 	if (!tmp)
// 		return (NULL);
// 	appendright(&token_list, tmp);
// 	return (token_list);
// }
//extract the content to add in a linked list node

// static bool	delimitor_except_blank(char c)
// {
// 	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
// 			&& c <= 'Z') || (c == '|') || (c == '\'') || (c == '"')
// 		|| (c == '|') || (c == '>') || (c == '<'))
// 		return (true);
// 	else
// 		return (false);
// }
// //delimitors except blanks: pipe, chevrons, quotes
// //to avoid putting each blank into a node

// static int	keep_blanks_quotes(char *input)
// {
// 	int	i;

// 	i = -1;
// 	if (!input)
// 		return (FAILURE);
// 	while (input[++i])
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 		{
// 			if (check_quotes(input) == FAILURE)
// 				return (FAILURE);
// 		}
// 	}
// 	return (SUCCESS);
// }
//keeps blanks if we are in quotes

// int	separator(t_shell *gear_5, t_env *envp)
// {
// 	int		i;
// 	int		start;
// 	bool	blank;

// 	i = -1;
// 	start = 0;
// 	blank = true;
// 	(void)envp;
// 	if (!gear_5)
// 		error("Empty gear_5\n");
// 	while (gear_5->input[++i])
// 	{
// 		if ((delimitor_except_blank(gear_5->input[i]) == true)
// 			&& (blank == true))
// 		{
// 			blank = false;
// 			start = i;
// 		}
// 		if (((i_am_delimitor(gear_5->input[i])) == SUCCESS) && (blank == false))
// 			blank = true;
// 		if ((gear_5->input[i] == '>') || (gear_5->input[i] == '<')
// 			|| (gear_5->input[i] == '|'))
// 		{
// 			ft_printf("j'entre ici");
// 			gear_5->input[i] = '@';
// 		}
// 		ft_printf("[%d]: %c\n", i, gear_5->input[i]);
// 	}
// 	ft_printf("%s\n", gear_5->input);
// 	return (SUCCESS);
// }
//function to separate entities

static void	malloc_strcpy(char *str, int start, int end)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * (end - start + 1));
	if (!ptr || !str)
		return ;
	while (str[start] && start < end)
	{
		ptr[i] = str[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	printf("ptr: %s\n", ptr);
	int j = -1;
	while (ptr[++j])
		printf("ptr[%d]: %c\n", j, ptr[j]);
}
//extracts the entity

static int	ft_strchr_quote(const char *str, char c)
{
	int	i;

	i = -1;
	if (!str || !c)
		return (FAILURE);
	while (str[++i])
	{
		if (str[i] == c)
			return (i + 1);
	}
	return (FAILURE);
}

// static bool	delimitor_except_blank(char c)
// {
// 	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
// 			&& c <= 'Z') || (c == '|') || (c == '\'') || (c == '"')
// 		|| (c == '|') || (c == '>') || (c == '<'))
// 		return (true);
// 	else
// 		return (false);
// }
//delimitors except blanks: pipe, chevrons, quotes
//to avoid putting each blank into a node

static bool	i_am_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
//check if it's space or tab

int	separator(t_shell *gear_5, t_env *envp)
{
	int	start;
	int	end;
	int	i;
	(void)envp;

	start = 0;
	end = 0;
	i = -1;
	while (gear_5->input[++i])
	{
		if ((ft_isalnum(gear_5->input[i]) == 0))
		{
			end = i;
			if (i_am_delimitor(gear_5->input[i]))
			{
				if (i_am_blank(gear_5->input[i]) == true)
				{
					printf("cc\n");
					continue ;
				}
				if (gear_5->input[i] == '\'')
					end += ft_strchr_quote(&gear_5->input[i + 1], '\'');
				else if (gear_5->input[i] == '"')
					end += ft_strchr_quote(&gear_5->input[i + 1], '"');
			}
			malloc_strcpy(gear_5->input, start, end);
			start = i;
		}
		//printf("Letter[%d]: %c\n", i, gear_5->input[i]);
	}
	return (SUCCESS);
}
//function to separate entities