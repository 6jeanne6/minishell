/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:38:40 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/11 14:36:45 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	create_or_update(t_token *list, t_env *envp)
{
	t_var	*current_var;
	char	*tmp_word;

	current_var = envp->first_variable;
	tmp_word = get_variable_name(list->word);
	while (current_var != NULL)
	{
		if (ft_strcmp(tmp_word, current_var->variable_name) == 0)
		{
			free(tmp_word);
			free(current_var->variable_value);
			current_var->variable_value = get_variable_value(list->word);
			print_var_list(envp->first_variable);
			return ;
		}
		current_var = current_var->next;
	}
	create_node(envp, list->word);
	print_var_list(envp->first_variable);
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

static void	variable_substitution(t_token *list, t_env *envp)
{
	t_var	*current_var;
	char	*word;
	int		flag;

	flag = 0;
	current_var = envp->first_variable;
	word = ft_strtrim(list->word, "$");
	if (!word)
		return ;
	while (current_var != NULL)
	{
		if (ft_strcmp(word, current_var->variable_name) == 0)
		{
			free(list->word);
			list->word = ft_strdup(current_var->variable_value);
			flag = 1;
			break ;
		}
		current_var = current_var->next;
	}
	if (flag == 0)
		empty_string(list);
	print_token_list(list);
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
			variable_substitution(list, envp);
		if (list_token->token_type == TOKEN_VARIABLEASSIGNATION)
			create_or_update(list, envp);
		if (list_token->token_type == TOKEN_ARG
			&& list_token->outer_double_quote == 1)
		{
			expand_double_quotes(list, envp);
			printf("This AFTER substitution\n");
			print_token_list(list);
		}
		list_token = list_token->next;
	}
}
// • variable $
//		→ exist = substitute with new value
// 		→ inexistant = display an empty string
// • variable assignation name=value
//		→ which variables ? a reflechir et voir au fur et a mesure