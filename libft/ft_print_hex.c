/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:11:13 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/02 09:42:45 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_dec_to_hex(char spec, unsigned int nbr, int *len)
{
	char	*hex_case;

	if (spec == 'x')
		hex_case = "0123456789abcdef";
	else
		hex_case = "0123456789ABCDEF";
	if (nbr >= 16)
		ft_dec_to_hex(spec, nbr / 16, len);
	ft_putchar_fd(hex_case[nbr % 16], 1);
	(*len)++;
}

void	ft_print_hex(char spec, va_list arg, int *len)
{
	int		nbr;

	nbr = va_arg(arg, unsigned int);
	ft_dec_to_hex(spec, nbr, len);
}
