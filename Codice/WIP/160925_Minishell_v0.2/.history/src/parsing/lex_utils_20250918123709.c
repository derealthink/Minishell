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

void	print_tokens(t_table *list)//temp
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

