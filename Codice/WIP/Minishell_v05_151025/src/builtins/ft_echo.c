/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/26 18:52:10 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(t_minishell *shell, char **args)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n')
		{
			j = 2;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				newline = 0;
				i++;
				continue ;
			}
		}
		break ;
	}
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

/*
int	ft_echo(t_minishell *shell, char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
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
*/