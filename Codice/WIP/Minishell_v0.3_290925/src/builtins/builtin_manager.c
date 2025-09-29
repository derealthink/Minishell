/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:39:14 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 16:54:56 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int is_builtin(char *cmd) // passiamo struct->args[0]
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
//		ft_strcmp(cmd[0], "$") == 0 && ft_strcmp(cmd[1], "?") != 0) 

		return (1);
	return (0);
}

int execute_builtin(t_cmd *cmd_list, char ***envp)
{
	if (ft_strcmp(cmd_list->args[0], "echo"))
		return (ft_echo(cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "cd"))
		return (ft_cd(cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "pwd"))
		return (ft_pwd());
	else if (ft_strcmp(cmd_list->args[0], "export"))
		return (ft_export(cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "unset"))
		return (ft_unset(cmd_list->args));
	else if (ft_strcmp(cmd_list->args[0], "env"))
		return (ft_env(*envp));
//	else if (ft_strcmp(cmd_list->args[0], "exit"))
//		return (ft_exit(cmd_list->args));
//	else if (ft_strcmp(cmd_list->args[0][0], "$") && (!ft_strcmp(cmd_list->args[0][1], "?")))
//		return (env_variable(cmd_list->args, envp));
	return (0);
}

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