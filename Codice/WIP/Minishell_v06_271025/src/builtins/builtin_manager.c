/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 14:53:26 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	execute_builtin(t_minishell *shell, t_cmd *cmd_list, char ***new_envp)
{
	if (ft_strcmp(cmd_list->args[0], "echo") == 0)
		return (ft_echo(shell, cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "cd") == 0)
		return (ft_cd(shell, cmd_list->args, *new_envp));
	else if (ft_strcmp(cmd_list->args[0], "pwd") == 0)
		return (ft_pwd(shell, *new_envp));
	else if (ft_strcmp(cmd_list->args[0], "export") == 0)
		return (ft_export(shell, cmd_list->args, *new_envp));
	else if (ft_strcmp(cmd_list->args[0], "unset") == 0)
		return (ft_unset(shell, cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "env") == 0)
		return (ft_env(shell, *new_envp));
	return (0);
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	is_child_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}
