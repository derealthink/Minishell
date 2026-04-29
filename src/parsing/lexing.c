/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:04:59 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 10:05:03 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!str)
		exit (1);
	i = 0;
	while (str[i])
	{
		advance = process_token_at_position(str, i, state, res);
		if (advance > 0)
			i += advance;
		else
		{
			state = state_tracker(str[i], state);
			i++;
		}
	}
	return (res);
}

int	process_token_at_position(char *str, int pos, t_state state, t_table *list)
{
	if (state == STATE_NORMAL && str[pos] == '\'')
		return (tokenizer_squotes(&str[pos], list));
	else if (state == STATE_NORMAL && str[pos] == '"')
		return (tokenizer_dquotes(&str[pos], list));
	else if (state == STATE_NORMAL && !is_space(str[pos]))
		return (tokenizer_norm(&str[pos], list));
	return (0);
}
