/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:55:08 by aielo             #+#    #+#             */
/*   Updated: 2025/05/17 14:39:48 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	len;
	size_t	i;

	if (!s || !f)
		return ;
	len = 0;
	while (s[len] != '\0')
		len++;
	i = 0;
	while (i < len)
	{
		(*f)(i, &s[i]);
		i++;
	}
}
