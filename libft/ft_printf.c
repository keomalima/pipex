/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:58:12 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/16 15:27:24 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	spec_check(char c, va_list args, int *len)
{
	if (c == 'd' || c == 'i' || c == 'u')
		ft_print_int(c, args, len);
	else if (c == 's' || c == 'c')
		ft_print_char(c, args, len);
	else if (c == 'x' || c == 'X')
		ft_print_hex(c, args, len);
	else if (c == 'p')
		ft_print_ptr(args, len);
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		(*len)++;
	}
}

void	str_parse(const char *format, va_list args, int *len)
{
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			spec_check(*++format, args, len);
		else
		{
			if (*format == '%')
				(*len) = -1;
			else
			{
				ft_putchar_fd(*format, 1);
				(*len)++;
			}
		}
		format++;
	}
}

int	ft_printf(const char *format, ...)
{
	int			len;
	va_list		args;

	len = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	str_parse(format, args, &len);
	va_end(args);
	return (len);
}
