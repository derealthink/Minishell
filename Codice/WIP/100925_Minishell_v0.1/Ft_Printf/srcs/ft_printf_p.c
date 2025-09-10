/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:05:18 by aielo             #+#    #+#             */
/*   Updated: 2025/07/01 14:28:38 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_null_pointer(t_flags *flag);

int	ft_format_identifier_p(va_list *arg_list, t_flags *flag)
{
	char			*str;
	void			*ptr;
	int				printed;
	uintptr_t		number;
	int				length;

	printed = 0;
	ptr = va_arg(*arg_list, void *);
	number = (uintptr_t) ptr;
	if (!ptr)
		return (printed += ft_null_pointer(flag));
	str = ft_itoa_p(number, 0);
	if (!str)
		return (0);
	length = ft_strlen(str);
	if (!flag->left)
		printed += ft_flag_width(flag, length + 2);
	ft_putstr_fd("0x", 1);
	printed += 2;
	ft_putstr_fd(str, 1);
	printed += length;
	if (flag->left)
		printed += ft_flag_width(flag, length + 2);
	free (str);
	return (printed);
}

static int	ft_null_pointer(t_flags *flag)
{
	int	printed;

	printed = 0;
	if (!flag->left && flag->width > 5)
		printed += ft_flag_width(flag, 5);
	printed += write(1, "(nil)", 5);
	if (flag->left && flag->width > 5)
		printed += ft_flag_width(flag, 5);
	return (printed);
}
