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

t_token	*sort_redir(t_token *token, t_cmd *table)
{
	t_token	*temp;

	temp = token;
	{
		if (!temp->moved && temp->type == TYPE_RIN)
		{
			temp->moved = 1;
			if (temp->next)
			{
				temp = temp->next;
				table->input_file = ft_strdup(temp->value);
				temp->moved = 1;
				return (temp->next);
			}
		}
		else if (temp->type == TYPE_ROUT)
		{
			temp->moved = 1;
			if (temp->next)
			{
				temp = temp->next;
				table->output_file = ft_strdup(temp->value);
				temp->moved = 1;
				return (temp->next);
			}
		}
	}
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

void	args_to_cmd(t_cmd *cmd, t_token *start)
{
	int		count;
	t_token	*temp;
	char	**n_args;
	int		i;

	count = 0;
	temp = start;
	while (temp && temp->type != TYPE_PIPE)
	{
		if (!temp->moved && temp->type == TYPE_ARG)
			count++;
		temp = temp->next;
	}
	n_args = malloc(sizeof(char *) * (count + 1));
	if (!n_args)
		return ;
	temp = start;
	i = 0;
	while (temp && temp->type != TYPE_PIPE)
	{
		if (!temp->moved && temp->type == TYPE_ARG)
		{
			n_args[i] = ft_strdup(temp->value);
			temp->moved = 1;
			i++;
		}
		temp = temp->next;
	}
	n_args[i] = NULL;
	cmd->args = n_args;
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

t_cmd	*parser(t_table *list, t_cmd *table)
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
}
