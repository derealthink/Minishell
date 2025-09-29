/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/09/25 18:01:38 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

static char	**get_path_dirs(char **envp);
static void	free_path_dirs(char **path_dirs);

/**
 * Find a command in PATH directories
 * @param cmd: command name to find
 * @param envp: environment variables
 * @return: allocated string with full path, or NULL if not found
 */
char *find_command_in_path(char *cmd, char **envp)
{
	char	**path_dirs;
	char	*result;
	
	if (!cmd || !envp)
		return (NULL);
	path_dirs = get_path_dirs(envp);
	if (!path_dirs)
		return (NULL);
	result = find_executable(cmd, path_dirs);
	free_path_dirs(path_dirs);
	return (result);
}

/**
 * Extract PATH directories from environment
 * @param envp: environment variables
 * @return: allocated array of path directories, or NULL
 */
static char **get_path_dirs(char **envp)
{
	int		i;
	char	*path_value;
	char	**path_dirs;
	
	i = 0;
	path_value = NULL;
	while (envp[i]) // Find PATH variable
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_value = envp[i] + 5;
			break;
		}
		i++;
	}
	if (!path_value)
		return (NULL);
	path_dirs = ft_split(path_value, ':');
	return (path_dirs);
}

static void free_path_dirs(char **path_dirs)
{
	int i;
	
	if (!path_dirs)
		return;
	i = 0;
	while (path_dirs[i])
	{
		free(path_dirs[i]);
		i++;
	}
	free(path_dirs);
}
