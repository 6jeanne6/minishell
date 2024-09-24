/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:45 by jewu              #+#    #+#             */
/*   Updated: 2024/09/24 11:29:49 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

//update exit status according to signal
void	update_signal_exit(t_shell *gear_5)
{
	if (!gear_5)
		return ;
	if (g_sig_flag == CTRL_C)
		gear_5->exit_status = 130;
	if (g_sig_flag == CTRL_BACKSLASH)
		gear_5->exit_status = 131;
}

//ctrl-\ = SIGQUIT
//	→ in dying child like cat = \Quit (core dumped)
void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_sig_flag == IN_PARENT)
		{
			error("Quit (core dumped)");
			write(1, "\n", 1);
			rl_on_new_line();
			g_sig_flag = CTRL_BACKSLASH;
		}
	}
}

//ctrl-C = SIGINT
//	→ nothing = ^C
//	→ something = something^C
//	→ in heredoc, see above + leave heredoc
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
		g_sig_flag = CTRL_C;
	}
}

//receive signal and do action
void	handle_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
//CTRL-D 
// void ctrl_d(void)
// {
//     // free ?
//     ft_putstr_fd("exit", 2);
//     exit (0);
// }
