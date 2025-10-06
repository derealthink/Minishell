/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:26:13 by uponci            #+#    #+#             */
/*   Updated: 2025/10/06 14:26:14 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int unclosed_quotes(char *str)
{
    int i;
    int quotes;

    i = 0;
    quotes = 0;
    while (str[i])
    {
        if ((str[i] == 34 || str[i] == 39) && quotes == '0')
            quotes = str[i];
        else if (str[i] == quotes)
            quotes = 0;
        i++;
    }
    return (quotes);
}
