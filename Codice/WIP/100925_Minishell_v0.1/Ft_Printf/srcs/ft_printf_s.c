/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:41:40 by aielo             #+#    #+#             */
/*   Updated: 2025/06/25 22:37:09 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_null_string(t_flags *flag);

int	ft_format_identifier_s(va_list *arg_list, t_flags *flag)
{
	char	*str;
	char	*orig_str;
	int		printed;
	int		length;

	printed = 0;
	str = va_arg(*arg_list, char *);
	if (!str)
		return (printed += ft_null_string(flag));
	orig_str = str;
	length = ft_strlen(str);
	length = ft_flag_pre_s(&flag->prec, length, &str);
	if (!flag->left)
		printed += ft_flag_width(flag, length);
	ft_putstr_fd(str, 1);
	printed += length;
	if (flag->left)
		printed += ft_flag_width(flag, length);
	if (str != orig_str)
		free(str);
	return (printed);
}

static int	ft_null_string(t_flags *flag)
{
	int	printed;

	printed = 0;
	if (!flag->left && flag->width > 6)
		printed += ft_flag_width(flag, 6);
	printed += write(1, "(null)", 6);
	if (flag->left && flag->width > 6)
		printed += ft_flag_width(flag, 6);
	return (printed);
}
