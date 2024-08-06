/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:38:40 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/08/06 17:40:56 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_var_list(t_var *var) 
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

static void create_node(t_env *envp, char *word)
{
    t_var *new_var;
	t_var *current_var;

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
        {
            current_var = current_var->next;
        }
        current_var->next = new_var;
        new_var->prev = current_var;
    }
}

static void create_or_update(t_token *list, t_env *envp)
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
            return;
        }
        current_var = current_var->next;
    }
    create_node(envp, list->word);
	printf("Je suis passé par la");
	print_var_list(envp->first_variable);
}

static void	variable_substitution(t_token *list, t_env *envp)
{
	t_var	*current_var;
	char	*word;
	int		flag;

	flag = 0;
	word = NULL;
	current_var = envp->first_variable;
	while (current_var != NULL)
	{
		word = ft_strtrim(list->word, "$");
		if (ft_strcmp(word, current_var->variable_name) == 0)
		{
			free (list->word);
			list->word = ft_strdup(current_var->variable_value);
			flag = 1;
			break;
		}
		current_var = current_var->next;
	}
	if (flag == 0)
	{
		word = ft_strdup("");
		list->word = word;
	}
	print_token_list(list);
}


void	expander(t_token *list, t_env *envp)
{
	t_token *list_token;

	list_token = list;
	if (list_token == NULL)
		return ;

	while (list_token != NULL)
	{
		if (list_token->token_type == TOKEN_VARIABLE)
			variable_substitution(list, envp);
		if (list_token->token_type == TOKEN_VARIABLEASSIGNATION)
			create_or_update(list, envp);
		list_token = list_token->next;
	}
}