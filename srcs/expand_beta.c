/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_beta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:51:02 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/18 19:06:08 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
typedef struct s_expand
{
	int			i;
	int			j;
	int			inside_double_quotes;
	int			inside_single_quotes;
	char		*expanded_line;
	t_env 		*env;
	const char	*line;
} t_expand;


/* Function to extract variable name*/
/*
static char	*extract_variable_name(const char *line, int start, int end) 
{
	char	*var_name;
	
	var_name  = malloc(sizeof(char) * (end - start) + 1);
	if (!var_name) 
		return (NULL);
	ft_strncpy(var_name, &line[start], end - start);
	var_name[end - start] = '\0';
	return (var_name);
} */

/* Function to check if the var is in the list */
/*
static char	*check_in_the_list(char *name, t_env *env)
{
	t_var	*current_var;

	current_var= env->first_variable;
	while (current_var != NULL) 
	{
		if (ft_strcmp(name, current_var->variable_name) == 0) 
			return (current_var->variable_value);
		current_var = current_var->next;
	}
	return (NULL);
} */

/*
/*Expand variables*/
/*
static void expand_variable(t_expand *expand)
{
	int		start;
	char	*var_name;
	char	*var_value;

	(expand->i)++;
	start = expand->i;
	while (isalnum(expand->line[expand->i]) || expand->line[expand->i] == '_') 
		(expand->i)++;
	var_name = extract_variable_name(expand->line, start, expand->i);
	if (var_name) 
	{
		var_value = check_in_the_list(var_name, expand->env);
		if (var_value) 
		{
			strcpy(&expand->expanded_line[expand->j], var_value);
			expand->j += strlen(var_value);
		} 
		free(var_name);
	}
}
*/

/*
static void	handle_q(t_expand *expand)
{
	if (expand->line[expand->i] == '"')
	{
		expand->inside_double_quotes = !expand->inside_double_quotes;
	}
	else if (expand->line[expand->i] == '\'')
	{
		expand->inside_single_quotes = !expand->inside_single_quotes;
	}
	expand->expanded_line[expand->j++] = expand->line[expand->i++];
} */


/* Function to calculate the new length of the expanded line */
/*
static int	count_new_len(const char *line, t_env *env)
{
	int i = 0;
	int len = 0;
	int start;
	char *var_name;
	char *var_value;

	while (line[i])
	{
		if (line[i] == '$' && (i == 0 || !isalnum(line[i - 1])) && !isspace(line[i + 1]))
		{
			i++;
			start = i;
			while (isalnum(line[i]) || line[i] == '_')
				i++;
			var_name = extract_variable_name(line, start, i);
			if (var_name)
			{
				var_value = check_in_the_list(var_name, env);
				if (var_value)
					len += strlen(var_value);
				free(var_name);
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len + 1);
} */

/*
char	*expander_test(t_env *env, const char *line)
{
	t_expand	expand;
	int 		line_len;

	line_len = count_new_len(line, env);
	ft_bzero(&expand, sizeof(expand));
	expand.env = env;
	expand.line = line;
	expand.expanded_line = malloc(line_len * 2 + 1);
	if (!expand.expanded_line) 
		return (NULL);
	while (expand.line[expand.i]) 
	{
		if (expand.line[expand.i] == '"' || expand.line[expand.i] == '\'')
			handle_q(&expand);
		else if (expand.line[expand.i] == '$' && !expand.inside_single_quotes)
			expand_variable(&expand);
		else 
			expand.expanded_line[expand.j++] = expand.line[expand.i++];
	}
	expand.expanded_line[expand.j] = '\0';

	return (expand.expanded_line);
}
*/