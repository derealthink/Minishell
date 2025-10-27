/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 11:38:24 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_echo_option(char **args, int *newline);

int	ft_echo(t_minishell *shell, char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = ft_echo_option(args, &newline);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (shell->last_exit_status = 0);
}

static int	ft_echo_option(char **args, int *newline)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n')
		{
			j = 2;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				*newline = 0;
				i++;
				continue ;
			}
		}
		break ;
	}
	return (i);
}
