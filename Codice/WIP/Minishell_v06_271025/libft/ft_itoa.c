/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:39:56 by aielo             #+#    #+#             */
/*   Updated: 2025/05/17 13:17:02 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_digits(long num);

char	*ft_itoa(int n)
{
	long	num;
	char	*str;
	size_t	len;

	num = n;
	len = count_digits(num);
	str = malloc (len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[len - 1] = ((num % 10) + '0');
		num = num / 10;
		len--;
	}
	return (str);
}

static size_t	count_digits(long num)
{
	size_t	len;

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
