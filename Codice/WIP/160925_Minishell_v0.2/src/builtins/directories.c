/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 14:46:17 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
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
	return (0);
}

int	ft_cd(char **args)
{
	char	*path;

	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("HOME environment variable not set.", 2);
			return (-1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd: ");
		return (-1);
	}
	return (0);
}

int	ft_pwd(void)
{
	char	*directory;

	directory = getcwd(NULL, 0)
	if (!directory)
	{
		perror("pwd: ");
		return (1);
	}
	printf("%s\n", directory);
	free(directory);
	return (0);
}
