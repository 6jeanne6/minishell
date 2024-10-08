/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:24:09 by jewu              #+#    #+#             */
/*   Updated: 2024/10/08 18:35:15 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

//generate new name of heredoc
static char	*generate_heredoc_filename(t_shell *gear_5)
{
	static int	i;
	char		*num;
	char		*file_name;

	num = ft_itoa(i);
	if (!num)
		return (NULL);
	file_name = ft_strjoin("heredoc", num);
	free(num);
	if (!file_name)
		return (NULL);
	gear_5->heredoc_tab[gear_5->h_index] = ft_calloc(ft_strlen(file_name) + 1,
			sizeof(char));
	if (!gear_5->heredoc_tab[i])
	{
		free(file_name);
		return (NULL);
	}
	ft_strlcpy(gear_5->heredoc_tab[gear_5->h_index],
		file_name, ft_strlen(file_name) + 1);
	gear_5->h_index++;
	return (file_name);
}

//add \n to delimiter and create heredoc name
int	init_variable(t_token *token, char **delimiter, char **heredoc_name,
t_shell *gear_5)
{
	if (!token || !gear_5)
		return (FAILURE);
	*delimiter = ft_strjoin(token->next->word, "\n");
	if (!(*delimiter))
		return (FAILURE);
	*heredoc_name = generate_heredoc_filename(gear_5);
	if (!(*heredoc_name))
	{
		free(*delimiter);
		return (FAILURE);
	}
	return (SUCCESS);
}

//dup STDIN in cpystrin
//for ctrl C redirect cpystdin to STDIN_FILENO
static void	gnl_here_doc(t_exec *exec, char *delimiter, t_shell *gear_5)
{
	char	*line;
	int		cpystdin;

	cpystdin = dup(STDIN_FILENO);
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while ((line && g_sig_flag != SIGINT))
	{
		get_next_line(-42);
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putstr_fd(line, exec->fd_in);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	free(line);
	line = NULL;
	if (g_sig_flag == SIGINT)
		gear_5->exit_status = 130;
	dup2(cpystdin, STDIN_FILENO);
	close(cpystdin);
	close(exec->fd_in);
}
/*
//delimiter + heredoc name
//open heredoc in exec->fd_in
//do gnl and reopen heredoc in exec->fd_in
//put a flag for heredoc_here and copy heredoc in exec->heredoc_file
int	create_heredoc(t_exec *exec, t_token *token, t_shell *gear_5)
{
	char	*delimiter;
	char	*heredoc_name;

	if (!exec || !token || !token->next)
		return (FAILURE);
	if (init_variable(token, &delimiter, &heredoc_name, gear_5) == FAILURE)
		return (FAILURE);
	exec->fd_in = open(heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->fd_in < 0)
	{
		perror("Error opening heredoc file");
		free(delimiter);
		free(heredoc_name);
		return (FAILURE);
	}
	signal(SIGINT, sigint_here_doc);
	signal(SIGQUIT, SIG_IGN);
	gnl_here_doc(exec, delimiter, gear_5);
	exec->fd_in = open(heredoc_name, O_RDONLY);
	exec->heredoc_here = true;
	if (exec->fd_in < 0 || g_sig_flag == SIGINT)
	{
		g_sig_flag = 0;
		return (clean_heredoc(delimiter, heredoc_name, exec, gear_5), FAILURE);
	}
	exec->heredoc_file = gear_5->heredoc_tab[gear_5->number_of_hd - 1];
	free(heredoc_name);
	free(delimiter);
	handle_signal();
	return (SUCCESS);
}
*/

// Handle heredoc creation process
static int	open_and_gnl_heredoc(t_exec *exec, char *heredoc_name,
char *delimiter, t_shell *gear_5)
{
	exec->fd_in = open(heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->fd_in < 0)
	{
		perror("Error opening heredoc file");
		free(delimiter);
		free(heredoc_name);
		return (FAILURE);
	}
	signal(SIGINT, sigint_here_doc);
	signal(SIGQUIT, SIG_IGN);
	gnl_here_doc(exec, delimiter, gear_5);
	exec->fd_in = open(heredoc_name, O_RDONLY);
	exec->heredoc_here = true;
	if (exec->fd_in < 0 || g_sig_flag == SIGINT)
	{
		g_sig_flag = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

//delimiter + heredoc name
//open heredoc in exec->fd_in
//do gnl and reopen heredoc in exec->fd_in
//put a flag for heredoc_here and copy heredoc in exec->heredoc_file
int	create_heredoc(t_exec *exec, t_token *token, t_shell *gear_5)
{
	char	*delimiter;
	char	*heredoc_name;

	if (!exec || !token || !token->next)
		return (FAILURE);
	if (init_variable(token, &delimiter, &heredoc_name, gear_5) == FAILURE)
		return (FAILURE);
	if (open_and_gnl_heredoc(exec, heredoc_name, delimiter, gear_5) == FAILURE)
		return (clean_heredoc(delimiter, heredoc_name, exec, gear_5), FAILURE);
	exec->heredoc_file = gear_5->heredoc_tab[gear_5->number_of_hd - 1];
	free(heredoc_name);
	free(delimiter);
	handle_signal();
	return (SUCCESS);
}
