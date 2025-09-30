/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:07:37 by aielo             #+#    #+#             */
/*   Updated: 2025/09/30 15:16:06 by aielo            ###   ########.fr       */
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
		if (ptr->value)
			free(ptr->value);
		free(ptr);
		ptr = next;
	}
	free(token_list);
}

void	cmd_list_clear(t_cmd *cmd_list)
{
	t_cmd	*next;
	t_cmd	*ptr;
	int		i;

	if (!cmd_list)
		return ;
	ptr = cmd_list;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->path)
			free(ptr->path);
		if (ptr->args)
		{
			i = 0;
			while (ptr->args[i])
			{
				free(ptr->args[i]);
				i++;
			}
			free(ptr->args);
		}
		if (ptr->input_file)
			free(ptr->input_file);
		if (ptr->output_file)
			free(ptr->output_file);
		if (ptr->delimiter)
			free(ptr->delimiter);
		free(ptr);
		ptr = next;
	}
}
