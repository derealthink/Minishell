/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:31:54 by aielo             #+#    #+#             */
/*   Updated: 2025/05/19 12:45:36 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*next;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		next = ptr->next;
		(*del)(ptr->content);
		free (ptr);
		ptr = next;
	}
	*lst = NULL;
}
