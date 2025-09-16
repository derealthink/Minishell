/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/09/15 17:39:39 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/**
 * Check if a command is a builtin (placeholder)
 * @param cmd: command name
 * @return: 1 if builtin, 0 otherwise
 */
int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    
    if (ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0)
        return (1);
    
    return (0);
}

/**
 * Execute builtin command (placeholder)
 * @param cmd: command structure
 * @param envp: environment variables
 * @return: exit status
 */
int execute_builtin(t_cmd *cmd, char ***envp)
{
    // Placeholder - implement your builtins here
    (void)cmd;
    (void)envp;
    return (0);
}