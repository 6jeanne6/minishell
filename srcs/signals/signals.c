/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:45 by jewu              #+#    #+#             */
/*   Updated: 2024/09/25 13:52:42 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

// update exit status according to signal
void	update_signal_exit(t_shell *gear_5)
{
	if (!gear_5)
		return ;
	if (g_sig_flag == CTRL_C || g_sig_flag == CTRL_C_HEREDOC)
		gear_5->exit_status = 130;
	if (g_sig_flag == CTRL_BACKSLASH)
		gear_5->exit_status = 131;
}

// ctrl-\ = SIGQUIT
//	→ in dying child like cat = \Quit (core dumped)
void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_sig_flag == IN_CHILD)
		{
			error("Quit (core dumped)");
			write(1, "\n", 1);
			rl_on_new_line();
			g_sig_flag = CTRL_BACKSLASH;
		}
		else if (g_sig_flag != IN_HEREDOC && g_sig_flag != IN_CHILD
			&& g_sig_flag != CTRL_BACKSLASH)
		{
			printf("\033[2D\033[0K");
			rl_on_new_line();
			rl_redisplay();
		}
		else if (g_sig_flag == IN_HEREDOC)
		{
			printf("\033[2D\033[0K");
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

// ctrl-C = SIGINT
//	→ nothing = ^C
//	→ something = something^C
//	→ in heredoc, see above + leave heredoc
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_sig_flag == IN_HEREDOC)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			write(1, "\n", 1);
			rl_redisplay();
			close(STDIN_FILENO);
			g_sig_flag = CTRL_C_HEREDOC;
		}
		else
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			write(1, "\n", 1);
			rl_redisplay();
			g_sig_flag = CTRL_C;
		}
	}
}

// receive signal and do action
void	handle_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
// CTRL-D
// void ctrl_d(void)
// {
//     // free ?
//     ft_putstr_fd("exit", 2);
//     exit (0);
// }
