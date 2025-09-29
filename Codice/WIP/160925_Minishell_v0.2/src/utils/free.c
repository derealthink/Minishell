/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:07:37 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 17:45:04 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	token_list_clear(t_table *token_list)
{
	t_token	*ptr;
	t_token	*next;

	if (!token_list)
		return ;
	ptr = token_list->head;
	while (ptr != NULL)
	{
		next = ptr->next;
//		free(ptr->value); token value malloc??
		free (ptr);
		ptr = next;
	}
	free(token_list);
}
/*
void	cmd_list_clear(t_cmd *cmd_list)
{
	t_cmd	*next;

	if (!cmd_list)
		return ;
	ptr = list->head;
	while (ptr != NULL)
	{
		next = ptr->next;
		//free(ptr->value);
		free (ptr);
		ptr = next;
	}
	free(list);
}
*/