/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/09/25 12:48:08 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1); //incaso di pipe ft_putstr_fd(args[i], fd)? o viene fatto da dup2?
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putendl_fd("", 1);
	return (0);
}
