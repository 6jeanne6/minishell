/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:37:20 by jewu              #+#    #+#             */
/*   Updated: 2024/10/23 14:40:39 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

//close all heredocs
void	close_heredoc(t_shell *gear_5)
{
	int	i;

	i = 0;
	if (!gear_5)
		return ;
	if (gear_5->heredoc_tab)
	{
		while (i < gear_5->number_of_hd - 1)
		{
			if (gear_5->heredoc_tab[i])
			{
				unlink(gear_5->heredoc_tab[i]);
				free(gear_5->heredoc_tab[i]);
				gear_5->heredoc_tab[i] = NULL;
			}
			i++;
		}
	}
	if (gear_5->number_of_hd > 0)
	{
		free(gear_5->heredoc_tab);
		gear_5->heredoc_tab = NULL;
	}
}

//in a child, if fd_in or fd_out == -1
void	invalid_fd_pipe(t_exec *exec, t_shell *gear_5, t_env *envp,
t_exec *head)
{
	if (!exec || !gear_5 || !envp || !head)
		return ;
	gear_5->exit_status = 1;
	close_files(head, gear_5);
}

//close all files when input is incorrect
void	error_close_files(t_exec *exec, t_shell *gear_5)
{
	t_exec	*current;

	if (!exec || !gear_5)
		return ;
	current = exec;
	while (current)
	{
		if (current->fd_in >= 3)
			close(current->fd_in);
		if (current->fd_out >= 3)
			close(current->fd_out);
		if (current->heredoc_here == true)
		{
			unlink(current->heredoc_file);
			free(current->heredoc_file);
		}
		current = current->next;
	}
	close_heredoc(gear_5);
}

//close all files when input is working
void	close_files(t_exec *exec, t_shell *gear_5)
{
	t_exec	*current;

	if (!exec || !gear_5)
		return ;
	current = exec;
	while (current)
	{
		if (current->fd_in >= 3)
			close(current->fd_in);
		if (current->fd_out >= 3)
			close(current->fd_out);
		if (current->heredoc_here == true)
		{
			close(current->fd_in);
			if (current->heredoc_file)
			{
				unlink(current->heredoc_file);
				free(current->heredoc_file);
			}
			current->heredoc_here = false;
		}
		current = current->next;
	}
	close_heredoc(gear_5);
}

//free delimiter and heredoc file if CTRL-C detecter or invalid fd_in
void	clean_heredoc(char *delimiter, char *heredoc_name, t_exec *exec,
t_shell *gear_5)
{
	int	i;

	i = -1;
	close_redir_fd(exec);
	free(delimiter);
	while (++i < gear_5->number_of_hd)
	{
		if (gear_5->heredoc_tab[i])
		{
			unlink(gear_5->heredoc_tab[i]);
			free(gear_5->heredoc_tab[i]);
			gear_5->heredoc_tab[i] = NULL;
		}
	}
	if (gear_5->number_of_hd > 0)
	{
		free(gear_5->heredoc_tab);
		gear_5->heredoc_tab = NULL;
	}
	free(heredoc_name);
	if (exec->bin)
	{
		free(exec->bin);
		exec->bin = NULL;
	}
}
