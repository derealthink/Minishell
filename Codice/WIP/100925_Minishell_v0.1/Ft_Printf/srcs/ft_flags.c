/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:09:10 by aielo             #+#    #+#             */
/*   Updated: 2025/06/25 19:12:35 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_flags(t_flags *flag)
{
	flag->left = 0;
	flag->zero = 0;
	flag->plus = 0;
	flag->space = 0;
	flag->sharp = 0;
	flag->width = -1;
	flag->prec = -1;
}

int	ft_check_flags(const char *format, t_flags *flag, int i)
{
	int		j;

	j = i;
	ft_set_flags(flag);
	while (format[i] && !ft_is_specifier(format[i]))
	{
		i = ft_check_flags_a(format, flag, i);
		i = ft_check_flags_b(format, flag, i);
	}
	return (i - j);
}

int	ft_check_flags_a(const char *format, t_flags *flag, int i)
{
	if (format[i] == '-')
	{
		flag->left = 1;
		i++;
		i = ft_find_size(format, i, &(flag->width));
	}
	else if (format[i] == '0')
	{
		flag->zero = 1;
		i++;
		i = ft_find_size(format, i, &(flag->width));
	}
	else if (ft_isdigit(format[i]))
		i = ft_find_size(format, i, &(flag->width));
	return (i);
}

int	ft_check_flags_b(const char *format, t_flags *flag, int i)
{
	if (format[i] == '+')
	{
		flag->plus = 1;
		i++;
	}
	else if (format[i] == ' ')
	{
		flag->space = 1;
		i++;
	}
	else if (format[i] == '#')
	{
		flag->sharp = 1;
		i++;
	}
	else if (format[i] == '.')
	{
		i++;
		i = ft_find_size(format, i, &(flag->prec));
	}
	return (i);
}

int	ft_find_size(const char *format, int i, int *size)
{
	int		k;
	char	str[200];

	k = 0;
	while (ft_isdigit(format[i]) && k < 199)
	{
		str[k] = format[i];
		k++;
		i++;
	}
	str[k] = '\0';
	*size = ft_atoi(str);
	return (i);
}
