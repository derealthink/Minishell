/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:21:03 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 10:21:08 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "types.h"

int	is_pipe(char *str)
{
	return (str && str[0] == '|' && str[1] == '\0');
}

int	is_rin(char *str)
{
	return (str && str[0] == '<' && str[1] == '\0');
}

int	is_rout(char *str)
{
	return (str && str[0] == '>' && str[1] == '\0');
}

int	is_append(char *str)
{
	return (str && str[0] == '>' && str[1] == '>' && str[2] == '\0');
}

int	is_heredoc(char *str)
{
	return (str && str[0] == '<' && str[1] == '<' && str[2] == '\0');
}
