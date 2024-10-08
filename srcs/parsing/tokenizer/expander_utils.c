/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:28:18 by jewu              #+#    #+#             */
/*   Updated: 2024/10/04 18:41:56 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to extract variable name*/
//from start to end length and copy the content inside
char	*extract_variable_name(const char *line, int start, int end)
{
	char	*var_name;

	var_name = malloc(sizeof(char) * (end - start) + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &line[start], end - start);
	var_name[end - start] = '\0';
	return (var_name);
}

/* Function to check if the var is in the list */
//if true then return the value of the variable
char	*check_in_the_list(char *name, t_env *env)
{
	t_var	*current_var;

	current_var = env->first_variable;
	while (current_var != NULL)
	{
		if (ft_strcmp(name, current_var->variable_name) == 0)
			return (current_var->variable_value);
		current_var = current_var->next;
	}
	return (NULL);
}

/* Expand the exit status*/
//do itoa of exit status to put in string in expanded line
//move j and i
void	expand_exit_status(t_expand *expand, t_shell *gear_5)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(gear_5->exit_status);
	if (exit_status_str)
	{
		ft_strcpy(&expand->expanded_line[expand->j], exit_status_str);
		expand->j += ft_strlen(exit_status_str);
		free(exit_status_str);
	}
	(expand->i)++;
}

/* Count len of the var in the list*/
void	handle_variable_in_list(t_expand *expand, char *var_name)
{
	char	*var_value;

	var_value = check_in_the_list(var_name, expand->env);
	if (var_value)
	{
		ft_strcpy(&expand->expanded_line[expand->j], var_value);
		expand->j += ft_strlen(var_value);
	}
	free(var_name);
}

/* Function to expand variables in the line */
//case of $?
void	expand_variable(t_expand *xpd, t_shell *shell)
{
	int		start;
	char	*var_name;

	(xpd->i)++;
	if (xpd->line[xpd->i] == '?')
		expand_exit_status(xpd, shell);
	else if (is_valid_character(xpd->line[xpd->i], xpd))
	{
		(xpd->i)++;
		return ;
	}
	else if (xpd->line[xpd->i] == '\0' || ft_isspace(xpd->line[xpd->i])
		|| xpd->line[xpd->i] == '"')
		xpd->expanded_line[xpd->j++] = '$';
	else
	{
		start = xpd->i;
		while (ft_isalnum(xpd->line[xpd->i])
			|| xpd->line[xpd->i] == '_')
			(xpd->i)++;
		var_name = extract_variable_name(xpd->line, start, xpd->i);
		if (var_name)
			handle_variable_in_list(xpd, var_name);
	}
}
