/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jewu <jewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:49:55 by jewu              #+#    #+#             */
/*   Updated: 2024/02/11 14:54:10 by jewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static	int	conversion(const char *str, va_list args)
{
	if (*(str + 1) == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if ((*(str) == '+') && (*(str + 1) == 'd' || *(str + 1) == 'i'))
		return (ft_printf_itoa_plus(va_arg(args, int)));
	else if ((*(str) == ' ') && (*(str + 1) == 'd' || *(str + 1) == 'i'))
		return (ft_printf_itoa_space(va_arg(args, int)));
	else if (*(str + 1) == 'd' || *(str + 1) == 'i')
		return (ft_printf_itoa(va_arg(args, int)));
	else if (*(str + 1) == 's')
		return (ft_printf_putstr(va_arg(args, char *)));
	else if (*(str + 1) == 'p')
		return (ft_printf_address(va_arg(args, unsigned long)));
	else if (*(str + 1) == 'u')
		return (ft_printf_uitoa(va_arg(args, unsigned int)));
	else if (*(str + 1) == 'x')
		return (ft_printf_hex(va_arg(args, unsigned int), 'x'));
	else if (*(str + 1) == 'X')
		return (ft_printf_hex(va_arg(args, unsigned int), 'X'));
	else if (*(str + 1) == '%')
		return (ft_putchar('%'));
	else
		return (-1);
}
/*
* The function conversion() manages different types of variables
* • Character c can be extracted with int 
*	→ types smaller than int (char) are promoted to int
*	→ it simplifies the processing of variable arguments
* • Pointers have a wide range of addresses
*	→ it depends on your computer architecture (32bits or 64bits)
*	→ 32bits systems stock 4Go of memory addresses, up to 4 billion
*/

static	int	input_iter(const char *string, va_list args)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			while (string[i + 1] == '+')
				i++;
			while (string[i + 1] == ' ')
				i++;
			result += conversion(&string[i], args);
			i++;
		}
		else
			result += ft_putchar(string[i]);
		i++;
	}
	return (result);
}
/*
*	Fonction pour parcourir la chaine input de ft_printf 
*/

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		output;

	if (!input)
		return (-1);
	va_start(args, input);
	output = input_iter(input, args);
	va_end(args);
	return (output);
}
/*
* Printf va ecrire chaque lettre jusqu'a ce que '\0' soit atteint.
* En meme temps il compte le nombre de caracteres ecrits en sortie.
* Si le caractere parcouru est %, on rentre dans la fonction conversion.
*/

/*
* 	~~~ Fonctions variadiques/Ellipse ~~~
*	int	ft_printf(const char *input, ...)
* • va_list	args = structure qui va stocker l'info 
* • void	va_start(va_list args, input) = macro qui initialise un objet va_list 
* 	pour parcourir les arguments variables
* • argument_type	va_arg(va_list argument_list, argument_type) 
*	→ macro qui recupere l'argument suivant de la liste
* 	→ avance automatiquement l'objet va_list a l'argument suivant
* • void	va_end(va_list variable_name) = cleans argument list
*	variables va_list
*/
