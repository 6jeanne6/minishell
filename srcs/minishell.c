/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:34:02 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/28 17:10:05 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

void	cleanup_exec(t_exec **exec, t_shell *gear_5)
{
	clean_exec(*exec, gear_5);
	free_exec(*exec);
	*exec = NULL;
}

//count how many <<
static void	count_n_create_heredoc(t_shell *gear_5, t_token *token)
{
	t_token	*tmp;

	if (!gear_5 || !token)
		return ;
	tmp = token;
	gear_5->number_of_hd = 0;
	gear_5->h_index = 0;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_HEREDOC)
			gear_5->number_of_hd++;
		tmp = tmp->next;
	}
	if (gear_5->number_of_hd > 0)
	{
		gear_5->heredoc_tab = ft_calloc(gear_5->number_of_hd + 1,
				sizeof(char *));
		if (!gear_5->heredoc_tab)
			return ;
	}
}

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
	if (is_dir(exec->cmd_name, gear_5) == SUCCESS)
	{
		if (exec->fd_in >= 3 && exec->heredoc_here == true)
		{
			close(exec->fd_in);
			unlink(exec->heredoc_file);
			close_heredoc(gear_5);
		}
		return (FAILURE);
	}
	signal(SIGINT, sigint_fork);
	flag = init_fork(gear_5, envp, exec);
	signal(SIGINT, sigint_handler);
	if (flag == FAILURE)
		return (FAILURE);
	if (flag != 42)
		gear_5->exit_status = child_status_code(gear_5);
	close_files(exec, gear_5);
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
			return (gear_5->exit_status = 127, FAILURE);
		get_token_type(envp, list);
		if (token_order(gear_5, list) == FAILURE)
			return (wrong_token_order(list, envp, gear_5), FAILURE);
		expander_two(envp, gear_5, &list);
		count_n_create_heredoc(gear_5, list);
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
int	processing_minishell(t_shell *gear_5, t_env *envp,
t_exec **exec, int *flag)
{
	t_token	*list;

	list = NULL;
	while (true)
	{
		reinit_everything(gear_5, exec);
		gear_5->input = readline("Super Gear 5 $> ");
		if (g_sig_flag == SIGINT)
			sigint_reset(gear_5);
		add_history(gear_5->input);
		if (gear_5->input == NULL)
			exit_ctrl_d(gear_5, *exec, envp);
		if (*flag == 0)
		{
			if (parse_gear_5(gear_5, envp, list, exec) == FAILURE)
				continue ;
			if (execute_gear_5(gear_5, envp, *exec) == FAILURE)
				continue ;
		}
		*flag = 0;
	}
	return (gear_5->exit_status);
}
