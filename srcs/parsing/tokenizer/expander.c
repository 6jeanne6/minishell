/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:51:02 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/14 15:47:44 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Flag to know if we in double or single quotes*/
//if we are inside a single/double quotes etc
void	handle_q(t_expand *expand)
{
	if (expand->line[expand->i] == '"')
		expand->inside_double_quotes = !expand->inside_double_quotes;
	else if (expand->line[expand->i] == '\'' && !expand->inside_double_quotes)
		expand->inside_single_quotes = !expand->inside_single_quotes;
	expand->expanded_line[expand->j++] = expand->line[expand->i++];
}

/* Count len part 2*/
//start after $, then go until the end of line
//extract this name variable and check if there is an existing variable in env
//if yes then return the length of this variable value
int	handle_variable_length(const char *line, int *i, t_env *env)
{
	int		start;
	char	*var_name;
	char	*var_value;
	int		var_len;

	var_len = 0;
	(*i)++;
	start = *i;
	if (ft_isalpha(line[*i]) || line[*i] == '_')
		(*i)++;
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
// if no $ then return length of line
// if $, following character must be alphabetic number or _
// += in the case of several environment variables in prompt
int	count_new_len(const char *line, t_env *env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (ft_strchr(line, '$') == 0)
	{
		len = ft_strlen(line);
		return (len);
	}
	while (line[i])
	{
		if ((line[i] == '$' && ft_isalpha(line[i + 1])) || line[i + 1] == '_')
			len += handle_variable_length(line, &i, env);
		else
		{
			len++;
			i++;
		}
	}
	return (len + 5);
}

/* Init expand structure */
//initialize with env, line and expanded line with
//length of new expanded line
static t_expand	init_expand(t_env *env, const char *line, int line_len)
{
	t_expand	expand;

	ft_bzero(&expand, sizeof(expand));
	expand.env = env;
	expand.line = line;
	expand.expanded_line = malloc(line_len + 1);
	if (!expand.expanded_line)
		expand.expanded_line = NULL;
	return (expand);
}

//count length of expanded line
//initialize expand structure
char	*expander_test(t_env *env, const char *line, t_shell *shell)
{
	t_expand	expand;
	int			line_len;

	line_len = count_new_len(line, env);
	expand = init_expand(env, line, line_len);
	if (expand.expanded_line == NULL)
		return (NULL);
	if (ft_strchr(line, '$') == 0 || find_double_angle_brackets(line) == 1)
		return (ft_strcpy(expand.expanded_line, line));
	while (expand.line[expand.i] != '\0' && expand.j < line_len)
	{
		if (expand.line[expand.i] == '"' || expand.line[expand.i] == '\'')
			handle_q(&expand);
		else if (expand.line[expand.i] == '$' && !expand.inside_single_quotes)
			expand_variable(&expand, shell);
		else if (expand.j < line_len)
			expand.expanded_line[expand.j++] = expand.line[expand.i++];
		else
			break ;
	}
	if (expand.j < line_len)
		expand.expanded_line[expand.j] = '\0';
	else
		expand.expanded_line[line_len - 1] = '\0';
	return (expand.expanded_line);
}
