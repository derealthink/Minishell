/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:25:21 by aielo             #+#    #+#             */
/*   Updated: 2025/05/16 13:23:09 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*empty_string(void);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
		i++;
	if (start >= i)
		return (empty_string());
	if (len > i - start)
		len = i - start;
	substr = (char *) malloc (sizeof (char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static char	*empty_string(void)
{
	char	*empty_s;

	empty_s = malloc(1);
	if (!empty_s)
		return (NULL);
	empty_s[0] = '\0';
	return (empty_s);
}
