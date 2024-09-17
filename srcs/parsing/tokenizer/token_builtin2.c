/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:15:23 by jewu              #+#    #+#             */
/*   Updated: 2024/09/17 12:23:17 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	arg = token;
	(void)envp;
	if (!arg->next)
		return (SUCCESS);
	else
	{
		arg = token->next;
		while (arg)
		{
			if (arg->token_type != TOKEN_ARG)
			{
				update_exit_status(gear_5, 1, NULL);
				return (FAILURE);
			}
			if (arg->next)
			{
				update_exit_status(gear_5, 1, NULL);
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
//so handle only number or arguments too?

int	unset_ok(t_shell *gear_5, t_token *token, t_env *envp)
{
	t_token	*arg;

	if (!gear_5 || !token || !envp)
		return (FAILURE);
	arg = token;
	if (!arg->next)
	{
		update_exit_status(gear_5, 1, NULL);
		return (FAILURE);
	}
	else
	{
		arg = arg->next;
		while (arg)
		{
			if (arg->token_type != TOKEN_ARG)
			{
				update_exit_status(gear_5, 1, NULL);
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
				update_exit_status(gear_5, 1, NULL);
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
		update_exit_status(gear_5, 1, NULL);
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
		update_exit_status(gear_5, 1, NULL);
		return (FAILURE);
	}
}
//pwd no options