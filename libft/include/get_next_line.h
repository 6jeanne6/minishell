/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:03:08 by jewu              #+#    #+#             */
/*   Updated: 2024/02/15 18:38:29 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

int		ft_strlen_gnl(char *s);
int		ft_strchr_gnl(char *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *s);
void	*ft_calloc_gnl(int nmemb, int size);

#endif
/*
 * sys/stat.h = manipulation of file metadata (modification date, rights)
 * fcntl.h = manipulate file descriptor
 * both libraries are used for open()
 * */
