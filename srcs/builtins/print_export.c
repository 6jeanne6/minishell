/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:28:22 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/24 16:29:39 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create new nodes in the list
static t_var	*duplicate_var(t_var *var)
{
	t_var	*new_var;

	new_var = malloc(sizeof(t_var));
	if (!new_var)
		return (NULL);
	new_var->variable_name = ft_strdup(var->variable_name);
	new_var->variable_value = ft_strdup(var->variable_value);
	new_var->flag = var->flag;
	new_var->next = NULL;
	new_var->prev = NULL;
	return (new_var);
}

// List cpy 
static t_var	*copy_env_vars(t_var *head)
{
	t_var	*copy_head;
	t_var	*copy_tail;
	t_var	*new_var;

	copy_head = NULL;
	copy_tail = NULL;
	while (head)
	{
		new_var = duplicate_var(head);
		if (!new_var)
			return (NULL);
		if (!copy_head)
		{
			copy_head = new_var;
			copy_tail = copy_head;
		}
		else
		{
			copy_tail->next = new_var;
			new_var->prev = copy_tail;
			copy_tail = new_var;
		}
		head = head->next;
	}
	return (copy_head);
}

// Swap var 
static void	swap_vars(t_var *a, t_var *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->variable_name;
	temp_value = a->variable_value;
	a->variable_name = b->variable_name;
	a->variable_value = b->variable_value;
	b->variable_name = temp_name;
	b->variable_value = temp_value;
}

// Sort list A-Z
static void	sort_env_vars(t_var *head)
{
	t_var	*i;
	int		swapped;

	if (!head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = head;
		while (i->next)
		{
			if (ft_strcmp(i->variable_name, i->next->variable_name) > 0)
			{
				swap_vars(i, i->next);
				swapped = 1;
			}
			i = i->next;
		}
	}
}

// Create a copy of the var env list 
// Sort this copy (A-Z)
// Print all environment variables of this list
// Free the tmp var list
void	print_all_env_var(t_env *env, int fd_out)
{
	t_var	*var;
	t_var	*copied_env;

	copied_env = copy_env_vars(env->first_variable);
	if (!copied_env)
		return ;
	sort_env_vars(copied_env);
	var = copied_env;
	while (var)
	{
		ft_putstr_fd("export ", fd_out);
		ft_putstr_fd(var->variable_name, fd_out);
		ft_putstr_fd("=\"", fd_out);
		ft_putstr_fd(var->variable_value, fd_out);
		ft_putstr_fd("\"\n", fd_out);
		var = var->next;
	}
	free_env_vars(copied_env);
}
