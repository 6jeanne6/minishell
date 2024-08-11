/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:07:52 by jewu              #+#    #+#             */
/*   Updated: 2024/08/11 18:18:29 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    pwd(t_shell *gear_5)
// {
//     char    *buffer;

//     if (!gear_5)
//         return ;
//     buffer = getcwd(NULL, 0);
//     if (buffer)
//     {
//         ft_putstr_fd(1, &buffer, ft_strlen(buffer));
//         free(buffer);
//     }
//     else
//         perror("pwd");
// }
//print current working directory
//pwd with no options, arguments ok