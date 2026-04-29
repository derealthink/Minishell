/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:56:09 by aielo             #+#    #+#             */
/*   Updated: 2025/10/16 18:51:13 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	list_size(void *lst)
{
	t_generic_list	*current;
	int				i;

	current = (t_generic_list *)lst;
	if (!current)
		return (0);
	i = 0;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0' && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
