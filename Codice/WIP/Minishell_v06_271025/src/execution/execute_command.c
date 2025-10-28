/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 16:08:42 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

int	execute_cmd(char *cmd_path, char **args, char **envp)
{
	char	*executable_path;

	if (!cmd_path || !args || !args[0])
		return (1);
	if (ft_strchr(cmd_path, '/'))
	{
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, args, envp);
			perror("execve failed");
		}
		else
			print_simple_error(cmd_path, "No such file or directory");
		return (1);
	}
	executable_path = find_command_in_path(cmd_path, envp);
	if (executable_path)
	{
		execve(executable_path, args, envp);
		perror("execve failed");
		free(executable_path);
	}
	else
    {
		if (is_parent_builtin(cmd_path))
			return (0); 
		print_unquoted_exe_error(cmd_path, "command not found");
	}
//	else
//		print_unquoted_exe_error(cmd_path, "command not found");
	return (1);
}

char	*find_executable(char *cmd, char **path_dirs)
{
	int		i;
	char	*temp_path;
	char	*full_path;

	if (!cmd || !path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		temp_path = ft_strjoin(path_dirs[i], "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
