/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/10/06 15:12:43 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

int execute_cmd(char *cmd_path, char **args, char **envp)
{
	char *executable_path;
	
	if (!cmd_path || !args || !args[0])
		return (1);
	if (ft_strchr(cmd_path, '/')) // If it's an absolute path, use it directly
	{
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, args, envp);
			perror("execve failed"); // This only runs if execve fails
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		return (1);
	}
	executable_path = find_command_in_path(cmd_path, envp); // Search in PATH
	if (executable_path)
	{
		execve(executable_path, args, envp);
		perror("execve failed"); // This only runs if execve fails
		free(executable_path);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_path, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (1);
}

char *find_executable(char *cmd, char **path_dirs)
{
	int		i;
	char	*temp_path;
	char	*full_path;
	
	if (!cmd || !path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		temp_path = ft_strjoin(path_dirs[i], "/"); // Join directory + "/" + command
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
