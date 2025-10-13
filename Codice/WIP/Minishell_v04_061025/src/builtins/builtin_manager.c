/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/10/08 13:25:36 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int execute_builtin(t_minishell *shell, t_cmd *cmd_list, char ***new_envp)
{
	if (ft_strcmp(cmd_list->args[0], "echo") == 0)
		return (ft_echo(cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "cd") == 0)
		return (ft_cd(shell, cmd_list->args, *new_envp)); //envp
	else if (ft_strcmp(cmd_list->args[0], "pwd") == 0)
		return (ft_pwd(*new_envp)); //envp
	else if (ft_strcmp(cmd_list->args[0], "export") == 0)
		return (ft_export(shell, cmd_list->args)); //shell
	else if (ft_strcmp(cmd_list->args[0], "unset") == 0)
		return (ft_unset(cmd_list->args)); //envp + shell
	else if (ft_strcmp(cmd_list->args[0], "env") == 0)
		return (ft_env(shell, *new_envp)); //envp
	return (0);
}

int is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0)
			return (1);
	return (0);
}

int is_child_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "env") == 0)
			return (1);
	return (0);
}

// shell lo uso per aggiornare shell->env_list->len_envp, cmd_list per avere commands e new_envp per aggiornare envp

/*
Builtins implementation

◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/

/*
echo - Echo the STRING(s) to standard output.
	-n do not output the trailing newline

cd - change the working directory
	chdir() changes the current working directory of the calling
	process to the directory specified in path.

pwd - print name of current/working directory


export - set an environment variable.

env - display, set, or remove environment variables,
	run a command in a modified environment.

unset - remove variable or function names.


exit - exit from a program, shell or log out of a Unix network.
*/