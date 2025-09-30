#include "parsing.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13 ))
		return (1);
	else
		return (0);
}

t_token	*new_token(char *value)
{
	t_token *tok = malloc(sizeof(t_token));
	tok->value = ft_strdup(value);
	tok->next = NULL;
	tok->type = 0;
	tok->moved = 0;
	return (tok);
}

t_table *init_list(void)
{
    t_table *list = malloc(sizeof(t_table));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int	is_quotes(char c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}

void	print_tokens(t_table *list)
{
	t_token	*current;
	int		count;

	if (!list || !list->head)
	{
		printf("Token list is empty\n");
		return;
	}
	current = list->head;
	count = 0;
	printf("=== LEXER OUTPUT ===\n");
	while (current)
	{
		printf("Token %d: [%s]\n", count, current->value);
		current = current->next;
		count++;
	}
	printf("Total tokens: %d\n", count);
	printf("==================\n");
}


void	print_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		cmd_count;
	int		arg_count;

	if (!cmd_list)
	{
		printf("Command list is empty (NULL)\n");
		return;
	}
	
	current = cmd_list;
	cmd_count = 0;
	
	printf("\n=== PARSER OUTPUT ===\n");
	while (current)
	{
		printf("\n--- Command %d ---\n", cmd_count);
		
		printf("Path: %s\n", current->path ? current->path : "(null)");
		
		if (current->args)
		{
			printf("Args: ");
			arg_count = 0;
			while (current->args[arg_count])
			{
				printf("[%s] ", current->args[arg_count]);
				arg_count++;
			}
			printf("(total: %d args)\n", arg_count);
		}
		else
		{
			printf("Args: (null)\n");
		}
		
		printf("Input file: %s\n", current->input_file ? current->input_file : "(null)");
		printf("Output file: %s\n", current->output_file ? current->output_file : "(null)");
		printf("Delimiter: %s\n", current->delimiter ? current->delimiter : "(null)");
		printf("Trunc mode: %d (1=truncate, 0=append)\n", current->trunc_mode);
		printf("Next command: %s\n", current->next ? "yes" : "no");
		
		current = current->next;
		cmd_count++;
	}
	
	printf("\nTotal commands: %d\n", cmd_count);
	printf("====================\n\n");
}
