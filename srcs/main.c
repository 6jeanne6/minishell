/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:11:17 by jewu              #+#    #+#             */
/*   Updated: 2024/10/08 18:30:12 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig_flag = 0;

int	init_minishell(t_shell *gear_5, t_env *envp)
{
	t_exec	*exec;
	int		flag;
	int		exit_status;

	flag = 0;
	exec = NULL;
	exit_status = processing_minishell(gear_5, envp, &exec, &flag);
	execve_clean_all(exec, envp, gear_5);
	return (exit_status);
}

//minishell only takes one argument
// • init gear_5 structure
//		→ which variables ? a reflechir et voir au fur et a mesure
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
	/*
	if (!isatty(STDOUT_FILENO))
		exit(FAILURE);
	*/
	ft_bzero(&gear_5, sizeof(t_shell));
	ft_bzero(&envp, sizeof(t_env));
	init_env(&envp, env);
	handle_signal();
	gear_5.exit_status = init_minishell(&gear_5, &envp);
	close(STDIN_FILENO);
	return (gear_5.exit_status);
}
