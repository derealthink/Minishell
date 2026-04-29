/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:07:45 by uponci            #+#    #+#             */
/*   Updated: 2025/11/03 13:03:00 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	unclosed_quotes(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
		{
			if (quotes == 0)
				quotes = str[i];
			else if (str[i] == quotes)
				quotes = 0;
		}
		i++;
	}
	return (quotes == 0);
}

int	pipe_misuse(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	len = ft_strlen(str);
	if (str[i] == '|' || str[len - 1] == '|')
		return (0);
	while (i < len)
	{
		if (str[i] == '|')
		{
			i++;
			while (i < len && is_space(str[i]))
				i++;
			if (i < len && str[i] == '|')
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	redir_misuse(char *str)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = ft_strlen(str);
	if (str[0] == '>' || str[len - 1] == '<' 
		|| str[len - 1] == '>')
		return (0);
	while (i < len)
	{
		if (str[i] == '<' || str[i] == '>')
		{
			count++;
			if (count > 2)
				return (0);
		}
		else
			count = 0;
		i++;
	}
	return (1);
}
