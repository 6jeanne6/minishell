/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_beta.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:51:02 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/09/23 18:43:50 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* Function to extract variable name*/
static char	*extract_variable_name(const char *line, int start, int end)
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
static char	*check_in_the_list(char *name, t_env *env)
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

static void	expand_exit_status(t_expand *expand, t_shell *gear_5)
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
static void	handle_variable_in_list(t_expand *expand, char *var_name)
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
static void	expand_variable(t_expand *expand, t_shell *shell)
{
	int		start;
	char	*var_name;

	(expand->i)++;
	if (expand->line[expand->i] == '?')
		expand_exit_status(expand, shell);
	else if (expand->line[expand->i] == '\0'
		|| ft_isspace(expand->line[expand->i])
		|| expand->line[expand->i] == '"')
		expand->expanded_line[expand->j++] = '$';
	else
	{
		start = expand->i;
		while (ft_isalnum(expand->line[expand->i])
			|| expand->line[expand->i] == '_')
			(expand->i)++;
		var_name = extract_variable_name(expand->line, start, expand->i);
		if (var_name)
			handle_variable_in_list(expand, var_name);
	}
}

/* Flag to know if we in double or single quotes*/
static void	handle_q(t_expand *expand)
{
	if (expand->line[expand->i] == '"')
		expand->inside_double_quotes = !expand->inside_double_quotes;
	else if (expand->line[expand->i] == '\'')
		expand->inside_single_quotes = !expand->inside_single_quotes;
	expand->expanded_line[expand->j++] = expand->line[expand->i++];
}

/* Count len part 2*/
static int	handle_variable_length(const char *line, int *i, t_env *env)
{
	int		start;
	char	*var_name;
	char	*var_value;
	int		var_len;

	var_len = 0;
	(*i)++;
	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var_name = extract_variable_name(line, start, *i);
	if (var_name)
	{
		var_value = check_in_the_list(var_name, env);
		if (var_value)
			var_len += ft_strlen(var_value);
		free(var_name);
	}
	return (var_len);
}

/* Function to calculate the new length of the expanded line */
static int	count_new_len(const char *line, t_env *env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$'
			&& (i == 0 || !ft_isalnum(line[i - 1]))
			&& !ft_isspace(line[i + 1]))
		{
			len += handle_variable_length(line, &i, env);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len + 1);
}

char	*expander_test(t_env *env, const char *line, t_shell *shell)
{
	t_expand	expand;
	int			line_len;

	line_len = count_new_len(line, env);
	ft_bzero(&expand, sizeof(expand));
	expand.env = env;
	expand.line = line;
	expand.expanded_line = malloc(line_len + 1);
	if (!expand.expanded_line)
		return (NULL);
	while (expand.line[expand.i])
	{
		if (expand.line[expand.i] == '"' || expand.line[expand.i] == '\'')
			handle_q(&expand);
		else if (expand.line[expand.i] == '$' && !expand.inside_single_quotes)
			expand_variable(&expand, shell);
		else
			expand.expanded_line[expand.j++] = expand.line[expand.i++];
	}
	expand.expanded_line[expand.j] = '\0';
	return (expand.expanded_line);
}
