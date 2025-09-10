/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:43 by aielo             #+#    #+#             */
/*   Updated: 2025/06/25 19:48:57 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_flag_pre_s(int *size, int length, char **str)
{
	int		prec;
	char	*tmp;

	prec = *size;
	if (prec < length && prec >= 0)
	{
		tmp = *str;
		*str = ft_substr(tmp, 0, prec);
		return (prec);
	}
	return (length);
}

int	ft_flag_pre_di(int *size, int length, int value)
{
	int	prec;
	int	zeros;

	prec = *size;
	if (prec == 0 && value == 0)
		return (0);
	if (prec > length)
	{
		zeros = prec - length;
		while (zeros > 0)
		{
			write(1, "0", 1);
			zeros--;
		}
		return (*size - length);
	}
	return (0);
}

int	ft_flag_pre_x(int *size, int length)
{
	int	prec;
	int	zeros;

	prec = *size;
	if (prec > length)
	{
		zeros = prec - length;
		while (zeros > 0)
		{
			write(1, "0", 1);
			zeros--;
		}
		return (*size - length);
	}
	return (0);
}
