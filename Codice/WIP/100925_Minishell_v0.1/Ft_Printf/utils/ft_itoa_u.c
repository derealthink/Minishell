/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:39:56 by aielo             #+#    #+#             */
/*   Updated: 2025/06/24 17:46:51 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	count_digits_u(unsigned int num);

char	*ft_itoa_u(unsigned int n)
{
	char			*str;
	unsigned int	len;

	len = count_digits_u(n);
	str = malloc (len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[len - 1] = ((n % 10) + '0');
		n = n / 10;
		len--;
	}
	return (str);
}

static unsigned int	count_digits_u(unsigned int num)
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
