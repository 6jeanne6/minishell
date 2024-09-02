/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/08/28 18:41:46 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//proceed to execution of Super_Gear_5 shell
// • execution:
//		→ pid
//		→ fork
//		→ waitpidb
//		→ close fds and pipes
static int	execute_gear_5(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	if (!gear_5 || !envp || !exec)
		return (FAILURE);
	if (is_builtin(exec->cmd_name))
	{	
		exec_builtin(gear_5, envp, exec);
		return(SUCCESS);
	}
	if (exec->bin)
	{
		execve(exec->bin, exec->args, envp->env);
		if (execve(exec->bin, exec->args, envp->env) < 0)
		{
			error("Check your execve\n");
			return (FAILURE);
		}
	}
	else
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

//• lexer
// 		→ Delimitor
// • parsing:
//		→ Extract words
//		→ Add to linked list
//		→ Tokenizer
//		→ Token order
//		→ Init t_exec structure with tab **args and redirections
static int	parse_gear_5(t_shell *gear_5, t_env *envp, t_token *list,
t_exec **exec)
{
	if (lexing_gear_5(gear_5) == SUCCESS)
	{
		free_token_list(list);
		list = NULL;
		extract_words(gear_5->input, &list);
		if (!list)
			return (update_exit_status(gear_5, 1));
		get_token_type(envp, list);
		print_token_list(list);
		if (token_order(list) == FAILURE)
		{
			//wrong_token_order(list, envp, gear_5);
			update_exit_status(gear_5, 2); 
			//free_token_list(list);
			return (FAILURE);
		}
		expander(list, envp);
		*exec = init_exec(gear_5, list, envp);
		/*
		if (!*exec)
		{
			free_t_exec(list, envp);
			// update_exit_status(gear_5, 1);
			return (FAILURE);
		}
		*/
		print_exec_list(*exec);
		free_token_list(list);
		return (SUCCESS);
	}
	return (FAILURE);
}

//Function to initialize minishell
// • env
// • lexer
// • parsing
// • execution
static int	init_minishell(t_shell *gear_5, t_env *envp)
{
	t_token	*list;
	t_exec	*exec;

	list = NULL;
	exec = NULL;
	while (true)
	{
		free_exec(exec);
		exec = NULL;
		gear_5->input = readline(WHITE"Super Gear 5 $> "RESET);
		add_history(gear_5->input);
		if (gear_5->input == NULL)
			break ;
		if (update_exit_status_code(gear_5) == SUCCESS)
			continue ;
		if (parse_gear_5(gear_5, envp, list, &exec) == FAILURE)
			continue ;
		if (execute_gear_5(gear_5, envp, exec) == FAILURE)
			continue ;
	}
	clean_env(envp);
	free_exec(exec);
	return (gear_5->exit_status);
}

int	main(int argc, char **argv, char **env)
{
	t_shell		gear_5;
	t_env		envp;

	(void)argv;
	if (argc > 1)
	{
		error("Error : Too many arguments\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&gear_5, sizeof(t_shell));
	ft_bzero(&envp, sizeof(t_env));
	init_env(&envp, env);
	gear_5.exit_status = init_minishell(&gear_5, &envp);
	return (gear_5.exit_status);
}
//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
// faire une fonction error au lieu de mettre ft_putstr_fd a chaque fois ?