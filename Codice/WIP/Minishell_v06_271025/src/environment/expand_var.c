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

char	*create_sub(char *tok)
{
	int		i;
	int		pos;
	size_t	len;
	char	*s;

	i = 0;
	while (tok[i] && tok[i] != '$')
		i++;
	pos = i;
	len = 1;
	i++;
	while (tok[i] && !is_space(tok[i]) && !is_quotes(tok[i]) && tok[i] != '$')
	{
		i++;
		len++;
	}
	s = ft_substr(tok, pos, len);
	return (s);
}

char	*env_find(char *tok, t_minishell *ms)
{
	t_new_envp	*temp;

	temp = ms->env_list->head;
	while (temp)
	{
		if (ft_strcmp(temp->name, tok) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

char	*process_sub(char *tok, t_minishell *ms)
{
	char	*res;

	if (!tok || tok[0] != '$')
		return (ft_strdup(tok));
	if (tok[1] == '\0')
		return (ft_strdup(""));
	if (tok[1] == '?')
		res = ft_itoa(ms->last_exit_status);
	else
		res = env_find(&tok[1], ms);
	return (res);
}

char	*env_str(char *tok, t_minishell *ms)
{
	int		i;
	int		pos;
	size_t	count;
	char	*rest;
	char	*temp;
	char	*exp;
	char	*res;
	char	*joined;

	i = 0;
	pos = 0;
	count = 0;
	res = ft_strdup("");
	while (tok[i])
	{
		pos = i;
		while (tok[i] && tok[i] != '$')
			i++;
		count = i - pos;
		if (count > 0)
		{
			rest = ft_substr(tok, pos, count);
			joined = ft_strjoin(res, rest);
			free(res);
			free(rest);
			res = joined;
		}
		if (tok[i] == '$')
		{
			temp = create_sub(&tok[i]);
			if (!temp)
				break ;
			exp = process_sub(temp, ms);
			joined = ft_strjoin(res, exp);
			free(res);
			free(exp);
			res = joined;
			i += ft_strlen(temp);
			free(temp);
		}
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
