/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:35:16 by jewu              #+#    #+#             */
/*   Updated: 2024/08/20 23:42:06 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free token list when token order is wrong
void    wrong_token_order(t_token *token, t_env *envp)
{
    if (!token || !envp)
        return ;
    free_token_list(token);
}