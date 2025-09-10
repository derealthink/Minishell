/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:05:18 by aielo             #+#    #+#             */
/*   Updated: 2025/07/01 14:25:45 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			ft_sign(int sign, int lenght, t_flags *flag);
static int			print_number(int number);
static unsigned int	count_digits(int num);
static void			ft_set_zero(t_flags *flag);

int	ft_format_identifier_di(va_list *arg_list, t_flags *flag)
{
	int		printed;
	int		number;
	int		length;
	int		sign;
	int		num_len;

	printed = 0;
	number = va_arg(*arg_list, int);
	sign = (number < 0);
	if (sign && number != INT_MIN)
		number = -number;
	length = count_digits(number);
	num_len = length;
	ft_set_zero(flag);
	if (flag->prec > length)
		num_len = flag->prec;
	printed += ft_sign(sign, num_len, flag);
	printed += ft_flag_pre_di(&flag->prec, length, number);
	if (number != INT_MIN)
		printed += print_number(number);
	else
		printed += write(1, "2147483648", 10);
	if (flag->left)
		printed += ft_flag_width(flag, printed);
	return (printed);
}

static int	print_number(int number)
{
	int		printed;
	char	*str;

	printed = 0;
	str = ft_itoa(number);
	if (!str)
		return (printed);
	ft_putstr_fd(str, 1);
	printed += ft_strlen(str);
	free (str);
	return (printed);
}

static unsigned int	count_digits(int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		len = 1;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

static int	ft_sign(int sign, int length, t_flags *flag)
{
	int		printed;
	int		prefix_bool;
	char	prefix;

	printed = 0;
	prefix_bool = 0;
	prefix = 0;
	if (sign)
		prefix = '-';
	else if (flag->plus)
		prefix = '+';
	else if (flag->space)
		prefix = ' ';
	if (prefix != 0)
		prefix_bool = 1;
	if (!flag->left && !flag->zero)
		printed += ft_flag_width(flag, length + prefix_bool);
	if (prefix)
	{
		ft_putchar_fd(prefix, 1);
		printed++;
	}
	if (!flag->left && flag->zero)
		printed += ft_flag_width(flag, length + prefix_bool);
	return (printed);
}

static void	ft_set_zero(t_flags *flag)
{
	if (flag->prec >= 0)
		flag->zero = 0;
}
