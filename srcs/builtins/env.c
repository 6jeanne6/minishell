/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:08:15 by jewu              #+#    #+#             */
/*   Updated: 2024/08/11 18:18:25 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    env(t_shell *gear_5, t_env *envp)
// {
//     t_var   *var;

//     if (!gear_5 || !envp)
//         return ;
//     var = envp->first_variable;
//     if (!var)
//         return ;
//     while (var)
//     {
//         ft_putstr_fd(var->variable_name, 1);
//         ft_putstr_fd("=", 1);
//         ft_putstr_fd(var->variable_value, 1);
//         ft_putstr_fd("\n", 1);
//         var = var->next;
//     }
//     gear_5->exit_status = 0;
// }
//env with no options or arguments