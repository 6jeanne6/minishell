/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:45 by jewu              #+#    #+#             */
/*   Updated: 2024/10/15 18:03:56 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

// Uptade exit status if a sigint 
void	sigint_reset(t_shell *gear_5)
{
	gear_5->exit_status = 130;
	g_sig_flag = 0;
}

// ctrl-\ = SIGQUIT
//	→ in dying child like cat = \Quit (core dumped)
void	sigquit_handler(int sig)
{
	g_sig_flag = sig;
	error("Quit (core dumped)");
	write(1, "\n", 1);
	rl_on_new_line();
}

// handle sigint in parent 
void	sigint_handler(int sig)
{
	g_sig_flag = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

// handle sigint heredoc
void	sigint_here_doc(int sig)
{
	g_sig_flag = sig;
	close(STDIN_FILENO);
	write(1, "\n", 1);
}

// receive signal and do action
void	handle_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
