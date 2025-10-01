#include "parsing.h"
#include "types.h"

void	type_tracking(t_table *tokens)
{
	t_token	*temp;
	printf("entering type_tracking\n");

	temp = tokens->head;
	while (temp)
	{
		if (is_pipe(temp->value))
			temp->type = TYPE_PIPE, printf("TYPE_PIPE\n");
		else if (is_append(temp->value))
			temp->type = TYPE_APP, printf("TYPE_APP\n");
		else if (is_heredoc(temp->value))
			temp->type = TYPE_HERED, printf("TYPE_HERED\n");
		 else if(is_rin(temp->value))
			temp->type = TYPE_RIN, printf("TYPE_RIN\n");
		else if (is_rout(temp->value))
			temp->type = TYPE_ROUT, printf("TYPE_ROUT\n");
		else
			temp->type = TYPE_ARG, printf("TYPE_ARG\n");
		temp = temp->next;
	}
}

t_token	*sort_redir(t_token *token, t_cmd *table)
{
	t_token *temp;

	temp = token;
	{
		if (temp->type == TYPE_RIN)
		{
			temp->moved = 1;
			if (temp->next)
			{
				temp = temp->next;//null checks
				table->input_file= ft_strdup(temp->value);
				temp->moved = 1;
				return (temp->next);
			}
		}
		else if (temp->type == TYPE_ROUT)
		{
			temp->moved = 1;
			if (temp->next)
			{
				temp = temp->next;//null checks
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
	t_token *temp;

	temp = token;
	printf("entered sort_app\n");
	if (temp->type == TYPE_APP)
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
	if (temp->type == TYPE_HERED)
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

void	args_to_cmd(t_cmd *cmd, t_table *list)
{

	int		count;
	t_token	*temp;
	char	**n_args;
	int		i;

	temp = list->head;
	count = 0;
	while (temp)
	{
		if(!temp->moved && temp->type == TYPE_ARG)
			count++;
		temp = temp->next;
	}
	n_args = malloc(sizeof(char*) * (count + 1));
	if (!n_args)
		return ;
	temp = list->head;
	i = 0;
	while (temp && i < count)
	{
		if (!temp->moved && temp->type == TYPE_ARG)
		{
			n_args[i] = ft_strdup(temp->value);
			temp->moved = 1;
			i++;
		}
		temp = temp->next;
	}
	n_args[count] = NULL;
	cmd->args = n_args;
}

t_token	*parser_loop(t_token *temp, t_cmd *table, t_table *list)
{
	
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
	args_to_cmd(table,list);
	return (temp);
}

t_cmd	*parser(t_table *list, t_cmd *table)// undestand how to handle double input or output update and free? or array of strings
{
	t_token	*temp;
	t_cmd	*pipe;

	if (table == NULL)
	{
		table = new_cmd(NULL);
		if (!table)
			return (NULL);
	}
	type_tracking(list);
	temp = list->head;
	if (!temp->moved)
		temp = parser_loop(temp, table, list);
	while(temp)
	{
		if (temp->type == TYPE_PIPE)
		{
			pipe = new_cmd(table);
			temp->moved = 1;
			if (temp->next)
			{
				temp = temp->next;
				table->next = pipe;
				table = pipe;
				if (!temp->moved)
					temp = parser_loop(temp, pipe, list);
			}
		}
		else
			temp = temp->next;
	}
	return (table);
}
