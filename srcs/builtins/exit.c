/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:08:26 by jewu              #+#    #+#             */
/*   Updated: 2024/08/11 18:18:18 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void exit(t_shell *gear_5, t_exec *execution)
// {
//     int i;
//     int status;

//     if (!execution || !gear_5)
//         return ;
//     i = 0;
//     status = 0;
//     while (execution->args[i])
//         i++;
//     if (i > 2)
//     {
//         gear_5->exit_status = 1;
//         error("pwd: too many arguments");
//         return ;
//     }
//     if (i == 2)
//     {
//         status = ft_atoi(execution->args[1])
//         if (ft_isdigit(status) == 0)
//             return ;
//         else
//             gear_5->exit_status = status;
//     }
//     exit(gear_5->exit_status);
// }
//exit with exit code specified
//exit with no options, but arguments ok