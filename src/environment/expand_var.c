/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:11:34 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 12:13:40 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static char	*append_plain_segment(char *tok, int *i, char *res)
{
	int		pos;
	size_t	count;
	char	*rest;
	char	*joined;

	pos = *i;
	while (tok[*i] && tok[*i] != '$')
		(*i)++;
	count = *i - pos;
	if (count == 0)
		return (res);
	rest = ft_substr(tok, pos, count);
	joined = ft_strjoin(res, rest);
	free(res);
	free(rest);
	return (joined);
}

static char	*append_env_segment(char *tok, int *i, char *res, t_minishell *ms)
{
	char	*temp;
	char	*exp;
	char	*joined;

	temp = create_sub(&tok[*i]);
	if (!temp)
		return (res);
	exp = process_sub(temp, ms);
	joined = ft_strjoin(res, exp);
	free(res);
	free(exp);
	*i += ft_strlen(temp);
	free(temp);
	return (joined);
}

char	*env_str(char *tok, t_minishell *ms)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (tok[i])
	{
		res = append_plain_segment(tok, &i, res);
		if (tok[i] == '$')
			res = append_env_segment(tok, &i, res, ms);
	}
	return (res);
}

void	find_env(t_minishell *ms)
{
	t_token	*temp;
	char	*res;

	temp = ms->token_list->head;
	while (temp)
	{
		if (is_env(temp->value) && !temp->s_quotes)
		{
			res = env_str(temp->value, ms);
			if (res)
			{
				free(temp->value);
				temp->value = res;
			}
		}
		temp = temp->next;
	}
}
