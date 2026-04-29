/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:51:47 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 13:51:49 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token	*handle_redir_type(t_token *temp, t_cmd *table, t_type type)
{
	if (!temp->moved && temp->type == type)
	{
		temp->moved = 1;
		if (temp->next)
		{
			temp = temp->next;
			if (type == TYPE_RIN)
				table->input_file = ft_strdup(temp->value);
			else if (type == TYPE_ROUT)
				table->output_file = ft_strdup(temp->value);
			temp->moved = 1;
			return (temp->next);
		}
	}
	return (NULL);
}

t_token	*sort_redir(t_token *token, t_cmd *table)
{
	t_token	*temp;
	t_token	*next;

	temp = token;
	next = handle_redir_type(temp, table, TYPE_RIN);
	if (next)
		return (next);
	next = handle_redir_type(temp, table, TYPE_ROUT);
	if (next)
		return (next);
	return (NULL);
}

t_token	*sort_app(t_token *token, t_cmd *table)
{
	t_token	*temp;

	temp = token;
	if (!temp->moved && temp->type == TYPE_APP)
	{
		temp->moved = 1;
		if (temp->next)
		{
			temp = temp->next;
			table->output_file = ft_strdup(temp->value);
			table->trunc_mode = 0;
			temp->moved = 1;
			return (temp->next);
		}
	}
	return (NULL);
}

t_token	*sort_herd(t_token *token, t_cmd *table)
{
	t_token	*temp;

	temp = token;
	if (!temp->moved && temp->type == TYPE_HERED)
	{
		temp->moved = 1;
		if (temp->next)
		{
			temp = temp->next;
			table->delimiter = ft_strdup(temp->value);
			temp->moved = 1;
			return (temp->next);
		}
	}
	return (NULL);
}
