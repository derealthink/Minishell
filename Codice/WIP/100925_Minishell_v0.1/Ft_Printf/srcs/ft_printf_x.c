/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:05:18 by aielo             #+#    #+#             */
/*   Updated: 2025/07/01 14:27:02 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			print_number(int number, char fi);
static unsigned int	count_digits(unsigned int num);
static void			print_sharp(char fi);

int	ft_format_identifier_x(char fi, va_list *arg_list, t_flags *flag)
{
	int				printed;
	unsigned int	number;
	int				length;

	printed = 0;
	number = va_arg(*arg_list, unsigned int);
	length = count_digits(number);
	if (flag->sharp && number > 0)
	{
		print_sharp(fi);
		printed = printed + 2;
		length = length + 2;
	}
	printed += ft_flag_pre_x(&flag->prec, length);
	if (!flag->left)
		printed += ft_flag_width(flag, length);
	printed += print_number(number, fi);
	if (flag->left)
		printed += ft_flag_width(flag, length);
	return (printed);
}

static int	print_number(int number, char fi)
{
	int		printed;
	char	*str;
	int		upper;

	printed = 0;
	upper = 0;
	if (fi == 'X')
		upper++;
	str = ft_itoa_x(number, upper);
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
		num = num / 16;
		len++;
	}
	return (len);
}

static void	print_sharp(char fi)
{
	if (fi == 'x')
		write(1, "0x", 2);
	else if (fi == 'X')
		write(1, "0X", 2);
}
