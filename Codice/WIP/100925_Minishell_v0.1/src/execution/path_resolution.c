/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/09/16 13:28:47 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

static char **get_path_dirs(char **envp);
static char *find_executable(char *cmd, char **path_dirs);
static void free_path_dirs(char **path_dirs);

/**
 * Main execution function for the pipeline
 * @param cmd_path: either absolute path or command name
 * @param args: pre-parsed argument array (including cmd as args[0])
 * @param envp: environment variables
 * @return: 0 on success, 1 on failure
 */

int execute_cmd(char *cmd_path, char **args, char **envp)
{
    char *executable_path;
    
    if (!cmd_path || !args || !args[0])
        return (1);
    
    // If it's an absolute or relative path, use it directly
    if (ft_strchr(cmd_path, '/'))
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
    
    // Search in PATH
    executable_path = find_command_in_path(cmd_path, envp);
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

/**
 * Find a command in PATH directories
 * @param cmd: command name to find
 * @param envp: environment variables
 * @return: allocated string with full path, or NULL if not found
 */
char *find_command_in_path(char *cmd, char **envp)
{
    char **path_dirs;
    char *result;
    
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
    int i;
    char *path_value;
    char **path_dirs;
    
    i = 0;
    path_value = NULL;
    
    // Find PATH variable
    while (envp[i])
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
    
    // Split PATH by ':'
    path_dirs = ft_split(path_value, ':');
    return (path_dirs);
}

/**
 * Search for executable in path directories
 * @param cmd: command name
 * @param path_dirs: array of PATH directories
 * @return: allocated full path string, or NULL if not found
 */
static char *find_executable(char *cmd, char **path_dirs)
{
    int i;
    char *temp_path;
    char *full_path;
    
    if (!cmd || !path_dirs)
        return (NULL);
    
    i = 0;
    while (path_dirs[i])
    {
        // Join directory + "/" + command
        temp_path = ft_strjoin(path_dirs[i], "/");
        if (!temp_path)
            return (NULL);
        
        full_path = ft_strjoin(temp_path, cmd);
        free(temp_path);
        
        if (!full_path)
            return (NULL);
        
        // Check if executable exists and is executable
        if (access(full_path, X_OK) == 0)
            return (full_path);
        
        free(full_path);
        i++;
    }
    return (NULL);
}

/**
 * Free array of path directories
 * @param path_dirs: array to free
 */
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
