/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:21:22 by aielo             #+#    #+#             */
/*   Updated: 2025/06/25 22:33:09 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_identifier_per(t_flags *flag)
{
	int		printed;

	printed = 0;
	if (!flag->left)
	{
		printed += ft_flag_width(flag, 1);
		ft_putchar_fd('%', 1);
		printed += 1;
	}
	else
	{
		ft_putchar_fd('%', 1);
		printed += 1;
		printed += ft_flag_width(flag, 1);
	}
	return (printed);
}
