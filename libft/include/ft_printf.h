/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:43:03 by jewu              #+#    #+#             */
/*   Updated: 2023/12/21 14:57:30 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>

int		ft_putchar(const char c);
int		ft_printf_itoa(int n);
int		ft_printf_uitoa(unsigned int n);
int		ft_printf_putstr(const char *str);
int		ft_printf(const char *input, ...);
int		ft_printf_address(unsigned long address);
int		ft_printf_hex(unsigned long num, char base);
int		ft_printf_itoa_plus(int n);
int		ft_printf_itoa_space(int n);

#endif

/*

• <stdlib.h> //manage memory dynamically, by 
allocating or freeing memory in the heap.

• <stdio.h> //manipulation of character streams 
(to a file or the console), managing your files.

• <ctype.h> //character processing, determine whether 
a character is of a certain type, and transformation functions.

• <string.h> //string manipulation and memory block
manipulation, <bsd/string.h> compile with -lbsd 

• <stdint.h> //sets of integer types with specified
widths and defines corresponding macro sets

• <unistd.h> //main POSIX API functions

• <stddef.h> //defines various variable types and macros (size_t) 

• <stdarg.h> library allows to use macros and functions when dealing with
variadic functions.

Variadic functions = A function with a fixed parameter + varying
number of arguments of varying types.

Fonction pour ecrire un caractere.

Utilise la librairie <unistd.h> qui utilise les fonctions de l'API POSIX.
Dans les annees 80, de nombreux OS derivent d'Unix : c'est la famille des 
systemes Unix.

Certains ont un noyau qui divergent du systeme originel : de fait, il est
impossible d'avoir un code C qui fonctionne sur tous les systemes.

POSIX : Portable Operating System Interface uniX

POSIX est un standard définissant l'interface de programmation 
(API : Application Programmation Interface) d'un noyau Unix en
definissant des normes techniques.

*/