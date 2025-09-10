/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:05:18 by aielo             #+#    #+#             */
/*   Updated: 2025/06/24 17:11:49 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_number(int number);
static unsigned int	count_digits(unsigned int num);

int	ft_format_identifier_u(va_list *arg_list, t_flags *flag)
{
	int				printed;
	unsigned int	number;
	int				length;

	printed = 0;
	number = va_arg(*arg_list, unsigned int);
	length = count_digits(number);
	printed += ft_flag_pre_di(&flag->prec, length, number);
	if (!flag->left)
		printed += ft_flag_width(flag, length);
	printed += print_number(number);
	if (flag->left)
		printed += ft_flag_width(flag, length);
	return (printed);
}

static int	print_number(int number)
{
	int		printed;
	char	*str;

	printed = 0;
	str = ft_itoa_u(number);
	if (!str)
		return (printed);
	ft_putstr_fd(str, 1);
	printed += ft_strlen(str);
	free (str);
	return (printed);
}

static unsigned int	count_digits(unsigned int num)
{
	unsigned int	len;

	len = 0;
	if (num <= 0)
		len = 1;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}
