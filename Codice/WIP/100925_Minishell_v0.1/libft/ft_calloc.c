/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:49:28 by aielo             #+#    #+#             */
/*   Updated: 2025/05/21 17:49:10 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*calloc_ptr;
	size_t			i;
	size_t			total_len;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	total_len = nmemb * size;
	calloc_ptr = malloc (total_len);
	if (!calloc_ptr)
		return (NULL);
	i = 0;
	while (i < total_len)
	{
		calloc_ptr[i] = '\0';
		i++;
	}
	return ((void *)calloc_ptr);
}
