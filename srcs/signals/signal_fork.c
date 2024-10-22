/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:42:24 by lnjoh-tc          #+#    #+#             */
/*   Updated: 2024/10/22 16:20:10 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

// handle sigint in fork
void	sigint_fork(int sig)
{
	g_sig_flag = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
}