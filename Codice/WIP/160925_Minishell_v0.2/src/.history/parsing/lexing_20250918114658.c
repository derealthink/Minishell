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

void	tokenizer_norm(char *str, t_state state, t_table *list)
{
	int		i;
	char	*token;
	t_token	*new;

	i = 0;
	while(str[i])
	{
		state = state_tracker(str[i], state);
		if (state == STATE_NORMAL && !is_space(str[i]))
		{
			token = str_div(&str[i]);
			new = new_token(token);
			free(token);
			if (!list->head)
				list->head = new;
			else
				list->tail->next = new;
			i += ft_strlen(new->value);
		}
		else
			i++;
	}
}

void	tokenizer_squotes(char *str, t_state state, t_table *list)
{
	int		i;
	char	*token;
	t_token	*new;

	i = 0;
	while(str[i])
	{
		state = state_tracker(str[i], state);
		if (state == STATE_SQUOTES)
		{
			token = str_div_q(&str[i]);
			new = new_token(token);
			free(token);
			if (!list->head)
				list->head = new;
			else
				list->tail->next = new;
			i += ft_strlen(new->value);
		}
		else
			i++;
	}
}

void	tokenizer_dquotes(char *str, t_state state, t_table *list)
{
	int		i;
	char	*token;
	t_token	*new;

	i = 0;
	while (str[i])
	{
		state = state_tracker(str[i], state);
		if (state == STATE_DQUOTES)
		{
			token = str_div_q(&str[i]);
			new = new_token(token);
			free(token);
			if (!list->head)
				list->head = new;
			else
				list->tail->next = new;
			i += ft_strlen(new->value);
		}
		else
			i++;
	}	
}

t_table	*lexer(char	*str)
{
	t_table	*res;
	t_state	state;
	int
	
	res = init_list();
	sate = STATE_NORMAL;
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
		while (!is_space(str[i]) && str[i] != '<' && str[i] != '>' && str[i] != '|')
		{
			count++;
			i++;
		}
	}
	else
	{
		while (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			count++;
			i++;
		}
	}
	return (res = ft_substr(str, start, count));
}

char	*str_div_q(char *str)
{
	int				i;
	size_t			count;
	unsigned int	start;
	char			*res;

	i = 0;
	count = 0;
	if (is_quotes(str[i]))
		i++;
	start = i;
	while (!is_quotes(str[i]))
	{
		count++;
		i++;
	}
	if (is_quotes(str[i]))
		i--;
	return (res = ft_substr(str, start, count));
}
