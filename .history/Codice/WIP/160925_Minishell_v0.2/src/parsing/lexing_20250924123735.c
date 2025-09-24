#include "parsing.h"

t_state	state_tracker(char c, t_state state)
{
	if (state == STATE_NORMAL)
	{
		if (c == '\'')
			return (STATE_SQUOTES);
		else if (c == '"')
			return (STATE_DQUOTES);
	}
	else if (state == STATE_SQUOTES && c == '\'')
		return (STATE_NORMAL);
	else if (state == STATE_DQUOTES && c == '"')
		return (STATE_NORMAL);
	return (state);
}

int	tokenizer_norm(char *str, t_table *list)
{
	char	*token;
	t_token	*new;
	int		token_len;

	token = str_div(str);
	if (!token)
		return (0);
	token_len = ft_strlen(token);
	new = new_token(token);
	free(token);
	if (!new)
		return (0);
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
	}
	else
	{
		list->tail->next = new;
		list->tail = new;
	}
	return (token_len);
}

int	tokenizer_squotes(char *str, t_table *list)
{
	char	*token;
	t_token	*new;
	int		token_len;

	token = str_div_q(str);
	if (!token)
		return (0);
	token_len = ft_strlen(token) + 2;
	new = new_token(token);
	free(token);
	if (!new)
		return (0);
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
	}
	else
	{
		list->tail->next = new;
		list->tail = new;
	}
	return (token_len);
}

int	tokenizer_dquotes(char *str, t_table *list)
{
	char	*token;
	t_token	*new;
	int		token_len;

	token = str_div_q(str);
	if (!token)
		return (0);
	token_len = ft_strlen(token) + 2;
	new = new_token(token);
	free(token);
	if (!new)
		return (0);
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
	}
	else
	{
		list->tail->next = new;
		list->tail = new;
	}
	return (token_len);
}

t_table	*lexer(char *str)
{
	t_table	*res;
	t_state	state;
	int		i;
	int		advance;

	res = init_list();
	if (!res)
		return (NULL);
	state = STATE_NORMAL;
	i = 0;
	while (str[i])
	{
		state = state_tracker(str[i], state);
		advance = process_token_at_position(str, i, state, res);
		if (advance > 0)
			i += advance;
		else
			i++;
	}
	return (res);
}

int	process_token_at_position(char *str, int pos, t_state state, t_table *list)
{
	if (state == STATE_NORMAL && !is_space(str[pos]))
		return (tokenizer_norm(&str[pos], list));
	else if (state == STATE_SQUOTES && str[pos] == '\'')
		return (tokenizer_squotes(&str[pos - 1], list));//this is not safe change to bounded logic
	else if (state == STATE_DQUOTES && str[pos] == '"')
		return (tokenizer_dquotes(&str[pos - 1], list));
	return (0);
}

char	*str_div(char *str)
{
	int				i;
	size_t			count;
	unsigned int	start;
	char			*res;

	i = 0;
	count = 0;
	while (is_space(str[i]))
		i++;
	start = i;
	if (str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		while (str[i] && !is_space(str[i]) && str[i] != '<' && str[i] != '>' && str[i] != '|' && !is_quotes(str[i]))
		{
			count++;
			i++;
		}
	}
	else
	{
		while (str[i] && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
		{
			count++;
			i++;
		}
	}
	res = ft_substr(str, start, count);
	return (res);
}

char	*str_div_q(char *str)//not edge case solid
{
	int				i;
	size_t			count;
	unsigned int	start;
	char			*res;
	//char			quote_char;

	i = 0;
	count = 0;
	//quote_char = str[i];
	if (is_quotes(str[i]))
		i++;
	start = i;
	while (str[i] && !is_quotes(str[i]))
	{
		count++;
		i++;
	}
	res = ft_substr(str, start, count);
	return (res);
}
