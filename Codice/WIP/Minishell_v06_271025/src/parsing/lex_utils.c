/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:54:54 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 09:55:05 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

t_token	*new_token(char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	tok->value = ft_strdup(value);
	tok->next = NULL;
	tok->type = 0;
	tok->moved = 0;
	tok->s_quotes = 0;
	tok->d_quotes = 0;
	return (tok);
}

t_table	*init_list(void)
{
	t_table	*list; 

	list = malloc(sizeof(t_table));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

int	is_quotes(char c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
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
	while (str[i] && !is_quotes(str[i]))
	{
		count++;
		i++;
	}
	res = ft_substr(str, start, count);
	return (res);
}
