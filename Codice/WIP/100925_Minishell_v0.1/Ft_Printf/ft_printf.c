/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:54:10 by aielo             #+#    #+#             */
/*   Updated: 2025/06/25 23:22:47 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	int		print_return;

	if (!format)
		return (1);
	print_return = 0;
	va_start(arg_list, format);
	print_return = ft_parse_and_print(format, &arg_list);
	va_end(arg_list);
	return (print_return);
}

int	ft_parse_and_print(const char *format, va_list *arg_list)
{
	t_flags	flag;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			i += ft_check_flags(format, &flag, i);
			count += ft_format_identifier(format[i], arg_list, &flag);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			count++;
			i++;
		}
	}
	return (count);
}

int	ft_format_identifier(char fi, va_list *arg_list, t_flags *flag)
{
	int		printed;

	printed = 0;
	if (fi == 'c')
		printed = ft_format_identifier_c(arg_list, flag);
	else if (fi == 's')
		printed = ft_format_identifier_s(arg_list, flag);
	else if (fi == 'd' || fi == 'i')
		printed = ft_format_identifier_di(arg_list, flag);
	else if (fi == 'u')
		printed = ft_format_identifier_u(arg_list, flag);
	else if (fi == 'x' || fi == 'X')
		printed = ft_format_identifier_x(fi, arg_list, flag);
	else if (fi == 'p')
		printed = ft_format_identifier_p(arg_list, flag);
	else if (fi == '%')
		printed = ft_format_identifier_per(flag);
	return (printed);
}

int	ft_is_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%');
}
