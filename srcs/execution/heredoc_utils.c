/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnjoh-tc <lnjoh-tc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:24:09 by jewu              #+#    #+#             */
/*   Updated: 2024/10/24 16:29:06 by lnjoh-tc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

//generate new name of heredoc
static char	*generate_heredoc_filename(t_shell *gear_5)
{
	char		*num;
	char		*file_name;

	num = ft_itoa(gear_5->h_index);
	if (!num)
		return (NULL);
	file_name = ft_strjoin("heredoc", num);
	free(num);
	if (!file_name)
		return (NULL);
	gear_5->heredoc_tab[gear_5->h_index] = ft_calloc(ft_strlen(file_name) + 1,
			sizeof(char));
	if (!gear_5->heredoc_tab[gear_5->h_index])
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
	*delimiter = ft_strdup(token->next->word);
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
static void	readline_here_doc(t_exec *exec, char *delimiter, t_shell *gear_5)
{
	char	*line;
	int		cpystdin;

	cpystdin = dup(STDIN_FILENO);
	line = readline("Heredoc>");
	while ((line && g_sig_flag != SIGINT))
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putstr_fd(line, exec->fd_in);
		ft_putstr_fd("\n", exec->fd_in);
		if (line)
			free(line);
		line = readline("Heredoc>");
	}
	free(line);
	line = NULL;
	if (g_sig_flag == SIGINT)
		gear_5->exit_status = 130;
	dup2(cpystdin, STDIN_FILENO);
	close(cpystdin);
	close(exec->fd_in);
}

// Handle heredoc creation process
static int	open_and_readline_heredoc(t_exec *exec, char *heredoc_name,
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
	readline_here_doc(exec, delimiter, gear_5);
	exec->fd_in = open(heredoc_name, O_RDONLY);
	exec->heredoc_here = true;
	if (exec->fd_in < 0 || g_sig_flag == SIGINT)
	{
		if (g_sig_flag == SIGINT)
		{
			gear_5->exit_status = 130;
			gear_5->interrupted = true;
			exec->heredoc_state = FAILURE;
		}
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
	if (open_and_readline_heredoc(exec, heredoc_name, delimiter, gear_5)
		== FAILURE)
		return (clean_heredoc(delimiter, heredoc_name, exec, gear_5), FAILURE);
	exec->heredoc_file = gear_5->heredoc_tab[gear_5->number_of_hd - 1];
	free(heredoc_name);
	free(delimiter);
	return (SUCCESS);
}
