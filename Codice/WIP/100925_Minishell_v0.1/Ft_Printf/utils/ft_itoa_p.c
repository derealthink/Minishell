/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 11:39:56 by aielo             #+#    #+#             */
/*   Updated: 2025/06/27 23:46:09 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

static unsigned int	count_digits_p(uintptr_t num);
static char			dec_to_hex(uintptr_t num, int upper);

char	*ft_itoa_p(uintptr_t n, int upper)
{
	char			*str;
	unsigned int	len;

	len = count_digits_p(n);
	str = malloc (len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[len - 1] = dec_to_hex(n, upper);
		n = n / 16;
		len--;
	}
	return (str);
}

static unsigned int	count_digits_p(uintptr_t num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		len = 1;
	while (num != 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

static char	dec_to_hex(uintptr_t num, int upper)
{
	unsigned int	hex;

	hex = num % 16;
	if (hex < 10)
		hex = hex + '0';
	else
	{
		if (upper == 0)
			hex = hex + 87;
		else if (upper == 1)
			hex = hex + 55;
	}
	return (hex);
}
