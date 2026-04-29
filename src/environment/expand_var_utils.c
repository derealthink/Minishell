/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:17:58 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 12:18:00 by uponci           ###   ########.fr       */
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
