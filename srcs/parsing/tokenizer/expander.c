/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:38:40 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/28 18:40:24 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	print_var_list(t_var *var) 
{
	int index = 0;
    while (var != NULL) {
        printf("Variable %d:\n", index);
        printf("  Name: %s\n", var->variable_name);
        printf("  Value: %s\n", var->variable_value);
        var = var->next;
        index++;
    }
}
//DEBUG FUNCTION
*/
/*
static void print_last_var(t_var *var) 
{
    // Parcourir la liste pour trouver le dernier élément
    t_var *last = var;
    if (last == NULL) {
        // Liste vide, rien à imprimer
        printf("No variables to display.\n");
        return;
    }
    
    while (last->next != NULL) {
        last = last->next;
    }

    // Afficher le dernier élément
    printf(" New var on the list :\n");
    printf("  Name: %s\n", last->variable_name);
    printf("  Value: %s\n", last->variable_value);
	printf("\n");
}
*/

static void	create_node(t_env *envp, char *word)
{
	t_var	*new_var;
	t_var	*current_var;

	new_var = (t_var *)malloc(sizeof(t_var));
	if (!new_var)
		return ;
	new_var->variable_name = get_variable_name(word);
	new_var->variable_value = get_variable_value(word);
	new_var->next = NULL;
	if (envp->first_variable == NULL)
	{
		new_var->prev = NULL;
		envp->first_variable = new_var;
	}
	else
	{
		current_var = envp->first_variable;
		while (current_var->next != NULL)
			current_var = current_var->next;
		current_var->next = new_var;
		new_var->prev = current_var;
	}
}
// • variable assignation name=value
//		→ add variable at the end of variable list

static void	create_or_update(t_token *token, t_env *envp)
{
	t_var	*current_var;
	char	*tmp_word;

	current_var = envp->first_variable;
	tmp_word = get_variable_name(token->word);
	while (current_var != NULL)
	{
		if (ft_strcmp(tmp_word, current_var->variable_name) == 0)
		{
			free(tmp_word);
			free(current_var->variable_value);
			current_var->variable_value = get_variable_value(token->word);
			return ;
		}
		current_var = current_var->next;
	}
	create_node(envp, token->word);
	// print_last_var(envp->first_variable);
	free(tmp_word);
}
// • variable assignation name=value
//		→ which variables ? a reflechir et voir au fur et a mesure

void	empty_string(t_token *list)
{
	free(list->word);
	list->word = ft_strdup("");
	if (!list->word)
		return ;
}
//if variable does not exist, display empty string

static void	variable_substitution(t_token *current_token, t_env *envp)
{
	t_var	*current_var;
	char 	*word;
	int		flag;

	flag = 0;
	current_var = envp->first_variable;
	word = ft_strtrim(current_token->word, "$");
	if (!word)
		return ;
	while (current_var != NULL)
	{
		if (ft_strcmp(word, current_var->variable_name) == 0)
		{
			free(current_token->word);
			current_token->word = ft_strdup(current_var->variable_value);
			flag = 1;
			break ;
		}
		current_var = current_var->next;
	}
	if (flag == 0)
		empty_string(current_token);
	free(word);
}

// • variable $
//		→ exist = substitute with new value
// 		→ inexistant = display an empty string

void	expander(t_token *list, t_env *envp)
{
	t_token	*list_token;

	list_token = list;
	if (list_token == NULL)
		return ;
	while (list_token != NULL)
	{
		if (list_token->token_type == TOKEN_VARIABLE)
			variable_substitution(list_token, envp);
		if (list_token->token_type == TOKEN_VARIABLEASSIGNATION
			&& (list_token->previous == NULL 
			|| list_token->previous->token_type == TOKEN_VARIABLEASSIGNATION))
		{
			if (ft_strchr(list_token->word, '$') 
			&& list_token->outer_single_quote == 0)
				expand_content(list_token, envp);
			create_or_update(list_token, envp);
		}
		if (list_token->token_type == TOKEN_ARG
			&& list_token->outer_single_quote == 0)
			expand_content(list_token, envp);
		list_token = list_token->next;
	}
}
