/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:24:09 by jewu              #+#    #+#             */
/*   Updated: 2024/09/24 18:27:55 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig_flag;

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

static void	stop_heredoc(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp)
{
	if (!gear_5 || !exec || !token || !envp)
		return ;
	//close(exec->fd_in);
	gear_5->exit_status = 130;
	//g_sig_flag = IN_PARENT;
}


//while to put line input in here_doc
static void	readline_here_doc(t_shell *gear_5, t_exec *exec, t_token *token,
t_env *envp)
{
	char	*line;

	if (!gear_5 || !envp || !exec)
		return ;
	g_sig_flag = IN_HEREDOC;
	while (true)
	{
		printf("debut of loop\n");
		line = readline("heredoc>");
		if (line == NULL || ft_strcmp(line, gear_5->delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (g_sig_flag == CTRL_C_HEREDOC)
		{
			close(exec->fd_in);
			stop_heredoc(gear_5, exec, token, envp);
			return ;
		}
		ft_putstr_fd(line, exec->fd_in);
		free(line);
	}
	close(exec->fd_in);
	g_sig_flag = IN_PARENT;
}

//handle <<
int	create_heredoc(t_shell *gear_5, t_exec *exec, t_token *token, t_env *envp)
{
	if (!gear_5 || !exec || !token || !envp)
		return (FAILURE);
	if (token->next)
	{
		gear_5->delimiter = ft_strjoin(token->next->word, "\n");
		if (!gear_5->delimiter)
			return (FAILURE);
		exec->fd_in = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (exec->fd_in < 0)
			return (free(gear_5->delimiter), FAILURE);
		readline_here_doc(gear_5, exec, token, envp);
		update_signal_exit(gear_5);
		exec->fd_in = open(".here_doc", O_RDWR, 0644);
		if (exec->fd_in < 0)
			return (free(gear_5->delimiter), FAILURE);
		exec->heredoc_file = ".heredoc";
		exec->heredoc_here = true;
		unlink(".here_doc");
		free(gear_5->delimiter);
	}
	return (SUCCESS);
}
