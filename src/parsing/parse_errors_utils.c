/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:07:45 by uponci            #+#    #+#             */
/*   Updated: 2025/11/03 13:03:02 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	hered_redir_check(char *str)
{
	if (str[0] == '<' && str[1] != '<')
		return (0);
	return (1);
}

int	hered_backtrail(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len && is_space(str[i]))
		i++;
	if (i < len && (str[i] == '<' && str[i] != '<'))
		return (0);
	return (1);
}

int	back_trail(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (!str)
		return (0);
	while (len > 0 && is_space(str[len - 1]))
		len--;
	if (len > 0 && (str[len -1] == '<' || str[len -1] == '>' 
			|| str[len -1] == '|'))
		return (0);
	while (i < len && is_space(str[i]))
		i++;
	if (i < len && (str[i] == '>' || str[i] == '|'))
		return (0);
	return (1);
}

int	pre_parse(char *str)
{
	if (!str)
		return (0);
	return (hered_backtrail(str) && back_trail(str) && hered_redir_check(str) 
		&& redir_misuse(str) && pipe_misuse(str) 
		&& unclosed_quotes(str));
}
