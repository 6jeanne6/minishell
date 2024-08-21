/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:15:23 by jewu              #+#    #+#             */
/*   Updated: 2024/08/21 16:12:27 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token;
	if (!arg->next)
		return (SUCCESS);
	else
	{
		arg = token->next;
		while (arg)
		{
			if (arg->token_type != TOKEN_ARG)
			{
				gear_5->exit_status = 1;
				error("exit: parse error\n");
				return (FAILURE);
			}
			if (arg->next)
			{
				gear_5->exit_status = 1;
				error("exit: too many arguments\n");
				return (FAILURE);
			}
			break ;
		}
	}
	return (SUCCESS);
}

//exit no options
//it means NUMBERS are OK like exit(42)
//it seems exit arg works (just one arg), 
// so handle only number or arguments too?
int	unset_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token;
	if (!arg->next)
	{
		gear_5->exit_status = 1;
		return (FAILURE);
	}
	else
	{
		arg = arg->next;
		while (arg)
		{
			if (arg->token_type != TOKEN_ARG)
			{
				error("unset: parse error\n");
				gear_5->exit_status = 1;
				return (FAILURE);
			}
			arg = arg->next;
		}
	}
	return (SUCCESS);
}

//unset no options
//unset VARIABLE_NAME VAR2 VAR3 ...
int	export_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token->next;
	if (!arg)
		return (SUCCESS);
	else
	{
		while (arg)
		{
			if (arg->token_type != TOKEN_VARIABLEASSIGNATION
				&& arg->token_type != TOKEN_ARG)
			{
				gear_5->exit_status = 1;
				error("export: check arguments\n");
				return (FAILURE);
			}
			arg = arg->next;
		}
	}
	return (SUCCESS);
}

//export no options
//export NAME=VALUE
//LOL=42 -------> export LOL
//export --------> displays environment variable 
int	env_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token;
	if (!arg->next)
		return (SUCCESS);
	else
	{
		gear_5->exit_status = 1;
		error("env: too many arguments\n");
		return (FAILURE);
	}
}

//env no options no arguments
int	pwd_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token;
	if (!arg->next)
		return (SUCCESS);
	else
	{
		gear_5->exit_status = 1;
		error("pwd: too many arguments\n");
		return (FAILURE);
	}
}
//pwd no options