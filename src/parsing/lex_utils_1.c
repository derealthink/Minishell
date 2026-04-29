/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:27:40 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 12:27:42 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	new->s_quotes = 1;
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
	new->d_quotes = 1;
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

static size_t	get_token_length(char *str, int i)
{
	size_t	count;

	count = 0;
	if (str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		while (str[i] && !is_space(str[i]) && str[i] != '<'
			&& str[i] != '>' && str[i] != '|' && !is_quotes(str[i]))
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
	return (count);
}

char	*str_div(char *str)
{
	int				i;
	size_t			count;
	unsigned int	start;
	char			*res;

	i = 0;
	while (is_space(str[i]))
		i++;
	start = i;
	count = get_token_length(str, i);
	res = ft_substr(str, start, count);
	return (res);
}
