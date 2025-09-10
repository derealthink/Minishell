/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:28 by aielo             #+#    #+#             */
/*   Updated: 2025/06/25 19:23:17 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_flag_width(t_flags *flag, int length)
{
	int		width;
	int		fill;
	char	fill_chr;

	width = flag->width;
	fill_chr = ' ';
	if (flag->zero && !flag->left && flag->prec < 0)
		fill_chr = '0';
	if (width > length)
	{
		fill = width - length;
		while (fill > 0)
		{
			write(1, &fill_chr, 1);
			fill--;
		}
		return (width - length);
	}
	return (0);
}
