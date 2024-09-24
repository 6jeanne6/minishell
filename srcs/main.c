/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/09/24 16:03:01 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_flag = 0;

//proceed to execution of Super_Gear_5 shell
// • execution:
//		→ pid
//		→ fork
//		→ waitpid
//		→ close fds and pipes
static int	execute_gear_5(t_shell *gear_5, t_env *envp, t_exec *exec)
{
	int	flag;

	flag = 0;
	if (!gear_5 || !envp || !exec)
		return (FAILURE);
	update_signal_exit(gear_5);
	flag = init_fork(gear_5, envp, exec);
	if (flag == FAILURE)
		return (FAILURE);
	if (flag != 42)
		gear_5->exit_status = child_status_code(gear_5);
	close_files(exec);
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
		extract_words(gear_5->input, &list, envp, gear_5);
		if (!list)
			return (update_exit_status(gear_5, 127, ""), FAILURE);
		get_token_type(envp, list);
		if (token_order(gear_5, list) == FAILURE)
			return (wrong_token_order(list, envp, gear_5), FAILURE);
		expander(list, envp);
		*exec = init_exec(gear_5, list, envp);
		if (!*exec)
		{
			free_t_exec(list, envp);
			return (FAILURE);
		}
		super_free_token_list(list);
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
		clean_exec(exec, gear_5);
		free_exec(exec);
		exec = NULL;
		g_sig_flag = IN_PARENT;
		gear_5->input = readline(WHITE"Super Gear 5 $> "RESET);
		update_signal_exit(gear_5);
		add_history(gear_5->input);
		if (gear_5->input == NULL)
			break ;
		is_dollar_question_mark_input(gear_5);
		if (parse_gear_5(gear_5, envp, list, &exec) == FAILURE)
			continue ;
		if (execute_gear_5(gear_5, envp, exec) == FAILURE)
			continue ;
	}
	execve_clean_all(exec, envp, gear_5);
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
	if (!isatty(STDOUT_FILENO))
		exit(FAILURE);
	ft_bzero(&gear_5, sizeof(t_shell));
	ft_bzero(&envp, sizeof(t_env));
	init_env(&envp, env);
	g_sig_flag = IN_PARENT;
	handle_signal();
	update_signal_exit(&gear_5);
	gear_5.exit_status = init_minishell(&gear_5, &envp);
	return (gear_5.exit_status);
}
//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
// faire une fonction error au lieu de mettre ft_putstr_fd a chaque fois ?