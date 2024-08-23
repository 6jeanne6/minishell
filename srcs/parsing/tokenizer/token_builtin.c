/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:10:15 by jewu              #+#    #+#             */
/*   Updated: 2024/08/23 15:54:41 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_path(char *path)
{
	if (!path || ft_strlen(path) == 0)
		return (FAILURE);
	if (path[0] == '/')
		return (SUCCESS);
	if ((ft_strcmp(path, ".") == 0) || (ft_strcmp(path, "..") == 0))
		return (SUCCESS);
	if ((access(path, F_OK) == 0) && (access(path, X_OK) == 0))
		return (SUCCESS);
	return (FAILURE);
}

//check for cd if it's a path
static int	cd_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token->next;
	if (!arg)
	{
		gear_5->exit_status = 1;
		return (FAILURE);
	}
	if ((arg->token_type != TOKEN_ARG) || (valid_path(arg->word) == FAILURE))
	{
		if ((ft_strcmp(arg->word, ".") != 0) && (ft_strcmp(arg->word, "..") != 0))
		{
			gear_5->exit_status = 1;
			error("cd: check your path\n");
			return (FAILURE);
		}
	}
	if (arg->next)
	{
		gear_5->exit_status = 1;
		error("cd: too many arguments\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

//cd [path] (absolute or relative)
static int	echo_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token->next;
	if (!arg)
		return (SUCCESS);
	while (arg)
	{
		if (arg->token_type == TOKEN_PIPE || arg->token_type == TOKEN_OUTPUT
			|| arg->token_type == TOKEN_APPEND || arg->token_type == TOKEN_INPUT
			|| arg->token_type == TOKEN_HEREDOC)
			break ;
		arg = arg->next;
	}
	if (arg && (arg == token->next))
	{
		gear_5->exit_status = 1;
		error("echo: parse error\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// echo -n -nnnnnnn ARG ARG ARG
static int	check_builtin(t_shell *gear_5, t_token *token, t_env *envp)
{
	if (ft_strcmp(token->word, "echo") == 0)
		return (echo_ok(gear_5, token, envp));
	if (ft_strcmp(token->word, "cd") == 0)
		return (cd_ok(gear_5, token, envp));
	if (ft_strcmp(token->word, "pwd") == 0)
		return (pwd_ok(gear_5, token, envp));
	if (ft_strcmp(token->word, "env") == 0)
		return (env_ok(gear_5, token, envp));
	if (ft_strcmp(token->word, "export") == 0)
		return (export_ok(gear_5, token, envp));
	if (ft_strcmp(token->word, "unset") == 0)
		return (unset_ok(gear_5, token, envp));
	if (ft_strcmp(token->word, "exit") == 0)
		return (exit_ok(gear_5, token, envp));
	return (FAILURE);
}

//which builtin are we on?

int	builtin_order(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*head;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	head = token;
	while (head)
	{
		if (head->token_type == TOKEN_BUILTIN)
		{
			if (check_builtin(gear_5, head, envp) == SUCCESS)
				return (SUCCESS);
		}
		head = head->next;
	}
	return (FAILURE);
}
//check builtin and the word following after