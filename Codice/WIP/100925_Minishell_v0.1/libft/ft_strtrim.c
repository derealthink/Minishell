/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:17:04 by aielo             #+#    #+#             */
/*   Updated: 2025/05/16 15:42:49 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_length(const char *s);
static size_t	start_point(char const *s1, char const *set);
static int		to_trim(const char *set, char c);
static char		*empty_string(void);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = start_point(s1, set);
	end = ft_length(s1);
	if (end == 0)
		return (empty_string());
	end--;
	while (end > start && to_trim(set, s1[end]))
		end--;
	if (start > end)
		return (empty_string());
	s2 = malloc((end - start + 1) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (start <= end)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}

static size_t	ft_length(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static size_t	start_point(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && to_trim(set, s1[i]))
		i++;
	return (i);
}

static int	to_trim(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
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
