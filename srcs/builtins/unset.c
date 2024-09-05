/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:14:54 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/05 14:32:41 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list *current;
    t_list *temp;

    while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
    {
        temp = *begin_list;
        *begin_list = (*begin_list)->next;
        free(temp);
    }

    current = *begin_list;
    while (current && current->next)
    {
        if (cmp(current->next->data, data_ref) == 0)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
}
 // Check si le tableau de args est non NULL
 // Si le tableau d'argument est NULL free et backslash N
 // Sinon parcourir le tableau pour trouver la variable 
 // Si la variable existe 

void unset(t_shell *shell)
{
	
}


 if (args == NULL)
	free 
	backslash n 
	return
else
	parcourir la liste de variable
	si la variable existe 
		la supprimée (free)
backslash n


typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;


void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list *current;
    t_list *temp;

    while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
    {
        temp = *begin_list;
        *begin_list = (*begin_list)->next;
        free(temp);
    }

    current = *begin_list;

    while (current && current->next)
    {
        if (cmp(current->next->data, data_ref) == 0)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
}