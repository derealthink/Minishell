/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:35:30 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 10:35:32 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "types.h"

void	type_tracking(t_table *tokens)
{
	t_token	*temp;

	temp = tokens->head;
	while (temp)
	{
		if (is_pipe(temp->value) && !temp->d_quotes && !temp->s_quotes)
			temp->type = TYPE_PIPE; 
		else if (is_append(temp->value) && !temp->d_quotes && !temp->s_quotes)
			temp->type = TYPE_APP;
		else if (is_heredoc(temp->value) && !temp->d_quotes && !temp->s_quotes)
			temp->type = TYPE_HERED;
		else if (is_rin(temp->value) && !temp->d_quotes && !temp->s_quotes)
			temp->type = TYPE_RIN;
		else if (is_rout(temp->value) && !temp->d_quotes && !temp->s_quotes)
			temp->type = TYPE_ROUT;
		else
			temp->type = TYPE_ARG;
		temp = temp->next;
	}
}

t_token	*parser_loop(t_token *temp, t_cmd *table)
{
	t_token	*start;

	start = temp;
	while (temp && temp->type != TYPE_PIPE)
	{
		if (temp->type == TYPE_RIN || temp->type == TYPE_ROUT)
			temp = sort_redir(temp, table);
		else if (temp->type == TYPE_APP)
			temp = sort_app(temp, table);
		else if (temp->type == TYPE_HERED)
			temp = sort_herd(temp, table);
		else
			temp = temp->next;
	}
	args_to_cmd(table, start);
	return (temp);
}

/*t_cmd	*parser(t_table *list, t_cmd *table)
{
	t_token	*temp;
	t_cmd	*pipe;
	t_cmd	*head;

	if (table == NULL)
	{
		table = new_cmd(NULL);
		if (!table)
			return (NULL);
		head = table;
	}
	type_tracking(list);
	temp = list->head;
	temp = parser_loop(temp, table);
	while (temp)
	{
		if (!temp->moved && temp->type == TYPE_PIPE)
		{
			pipe = new_cmd(table);
			if (temp->next)
			{
				temp = temp->next;
				table->next = pipe;
				table = pipe;
				temp = parser_loop(temp, pipe);
			}
		}
		else
			temp = temp->next;
	}
	return (head);
}*/

static t_token	*handle_pipe_token(t_token *temp, t_cmd **table)
{
	t_cmd	*pipe;

	pipe = new_cmd(*table);
	if (temp->next)
	{
		temp = temp->next;
		(*table)->next = pipe;
		*table = pipe;
		temp = parser_loop(temp, pipe);
	}
	return (temp);
}

t_cmd	*parser(t_table *list, t_cmd *table)
{
	t_token	*temp;
	t_cmd	*head;

	if (table == NULL)
	{
		table = new_cmd(NULL);
		if (!table)
			return (NULL);
		head = table;
	}
	type_tracking(list);
	temp = list->head;
	temp = parser_loop(temp, table);
	while (temp)
	{
		if (!temp->moved && temp->type == TYPE_PIPE)
			temp = handle_pipe_token(temp, &table);
		else
			temp = temp->next;
	}
	return (head);
}
