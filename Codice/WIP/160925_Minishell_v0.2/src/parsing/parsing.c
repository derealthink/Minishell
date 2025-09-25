#include "parsing.h"
#include "types.h"

void	type_tracking(t_table tokens)
{
	t_token	*temp;

	temp = tokens.head;
	while (temp)
	{
		if(is_redir(temp->value))
			temp->type = TYPE_REDIR;
		else if (is_pipe(temp->value))
			temp->type = TYPE_PIPE;
		else if (is_append(temp->value))
			temp->type = TYPE_APP;
		else if (is_heredoc(temp->value))
			temp->type = TYPE_HERED;
		else
			temp->type = TYPE_ARG;
		temp = temp->next;
	}
}

void	sort_redir(t_table tokens, t_cmd table)
{
	t_token *temp;

	temp = tokens.head;
	while(temp)
	{
		if (temp->type == TYPE_REDIR)
		{
			temp->moved = 1;
			temp = temp->next;
			table
		}
	}

}


