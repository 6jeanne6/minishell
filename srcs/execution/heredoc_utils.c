/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:24:09 by jewu              #+#    #+#             */
/*   Updated: 2024/09/30 12:02:55 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

//*********** GNL VERSION ***********/
//while to put line input in here_doc
// static void	gnl_here_doc(t_exec *exec, char *delimiter)
// {
// 	char	*line;

// 	ft_putstr_fd("heredoc>", 0);
// 	line = get_next_line(0);
// 	while (line)
// 	{
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			get_next_line(-42);
// 			break ;
// 		}
// 		ft_putstr_fd(line, exec->fd_in);
// 		free(line);
// 		ft_putstr_fd("heredoc>", 0);
// 		line = get_next_line(0);
// 	}
// 	close(exec->fd_in);
// }

// //handle <<
// int	create_heredoc(t_exec *exec, t_token *token)
// {
// 	char	*delimiter;

// 	if (!exec || !token)
// 		return (FAILURE);
// 	if (token->next)
// 	{
// 		delimiter = ft_strjoin(token->next->word, "\n");
// 		if (!delimiter)
// 			return (FAILURE);
// 		exec->fd_in = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		if (exec->fd_in < 0)
// 			return (free(delimiter), FAILURE);
// 		gnl_here_doc(exec, delimiter);
// 		exec->fd_in = open(".here_doc", O_RDWR, 0644);
// 		if (exec->fd_in < 0)
// 			return (free(delimiter), FAILURE);
// 		exec->heredoc_file = ".heredoc";
// 		exec->heredoc_here = true;
// 		unlink(".here_doc");
// 		free(delimiter);
// 	}
// 	return (SUCCESS);
// }
//*********** GNL VERSION ***********/

//*********** READLINE VERSION (NOT WORKING)***********/
// //while to put line input in here_doc
// static void	gnl_here_doc(t_shell *gear_5, t_exec *exec, char *delimiter)
// {
// 	char	*line;

// 	ft_putstr_fd("heredoc>", 0);
// 	line = get_next_line(0);
//  g_sig_flag = IN_HEREDOC;
// 	while (line)
// 	{
// 		if (ft_strcmp(line, delimiter) == 0 || g_sig_flag == CTRL_C_HEREDOC)
// 		{
// 			gear_5->sigint_heredoc = true;
// 			free(line);
// 			get_next_line(-42);
// 			break ;
// 		}
// 		ft_putstr_fd(line, exec->fd_in);
// 		free(line);
// 		ft_putstr_fd("heredoc>", 0);
// 		line = get_next_line(0);
// 	}
// 	is_dollar_question_mark_input(gear_5);
// 	close(exec->fd_in);
// 	g_sig_flag = IN_PARENT;
// }

// static void	heredoc_signals(t_shell *gear_5, t_exec *exec, t_token *token,
// t_env *envp)
// {
// 	if (!gear_5 || !exec || !token || !envp)
// 		return ;
// 	if (g_sig_flag == CTRL_C_HEREDOC)
// 	{
// 		close(exec->fd_in);
// 		//stop_heredoc(gear_5, exec, token, envp);
// 		return ;
// 	}
// }

// //while to put line input in here_doc
// static void	readline_here_doc(t_shell *gear_5, t_exec *exec, t_token *token,
// t_env *envp)
// {
// 	char	*line;

// 	if (!gear_5 || !envp || !exec)
// 		return ;
// 	g_sig_flag = IN_HEREDOC;
// 	while (true)
// 	{
// 		line = readline("heredoc>");
// 		heredoc_signals(gear_5, exec, token, envp);
// 		if (g_sig_flag == CTRL_C_HEREDOC)
// 			return ;
// 		if (line == NULL)
// 		{
// 			error("warning: here-document delimited by end of file\n");
// 			write(1, "\0", 1);
// 			break ;
// 		}
// 		if (ft_strcmp(line, gear_5->delimiter) == 0)
// 			return (free(line));
// 		ft_putstr_fd(line, exec->fd_in);
// 		free(line);
// 	}
// 	close(exec->fd_in);
// 	g_sig_flag = IN_PARENT;
// }

// //handle <<
// int	create_heredoc(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp)
// {
// 	int	status;

// 	if (!gear_5 || !exec || !token || !envp)
// 		return (FAILURE);
// 	if (token->next)
// 	{
// 		gear_5->delimiter = token->next->word;
// 		exec->fd_in = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		if (exec->fd_in < 0)
// 			return (free(gear_5->delimiter), FAILURE);
// 		gear_5->here_doc_pid = fork();
// 		if (gear_5->here_doc_pid < -1)
// 			return (FAILURE);
// 		else if (gear_5->here_doc_pid == 0)
// 		{
// 			readline_here_doc(gear_5, exec, token, envp);
// 			update_signal_exit(gear_5);
// 			exit(SUCCESS);
// 		}
// 		else
// 		{
// 			waitpid(gear_5->here_doc_pid, &status, 0);
// 			if (WIFSIGNALED(status))
// 			{
// 				gear_5->exit_status = 130;
// 				return (FAILURE);
// 			}
// 			exec->fd_in = open(".here_doc", O_RDWR, 0644);
// 			if (exec->fd_in < 0)
// 				return (free(gear_5->delimiter), FAILURE);
// 			exec->heredoc_file = ".heredoc";
// 			exec->heredoc_here = true;
// 			unlink(".here_doc");
// 		}
// 	}
// 	return (SUCCESS);
// }
//*********** READLINE VERSION (NOT WORKING)***********/

