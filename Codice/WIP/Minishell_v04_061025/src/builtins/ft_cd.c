/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/08 13:23:43 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_minishell *shell, char **args, char **new_envp)
{
	char	*path;
	char	*directory;
//	char	*tmp;
	int		i;

	i = 0;
	directory = getcwd(NULL, 0);
	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		while (new_envp[i])
		{
			if (ft_strncmp(new_envp[i], "HOME=", 5) == 0)
			{
				path = new_envp[i] + 5;
				break ;
			}
			i++;
		}
		if (path == NULL)
		{
			print_simple_error("cd", "HOME not set");
			return (shell->last_exit_status = 1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		print_unquoted_error("cd", path, "No such file or directory");
		return (shell->last_exit_status = 1);
	}
	//update OLD_PWD
	directory = getcwd(NULL, 0);
	//update PWD
	free(directory);
	return (shell->last_exit_status = 0);
}
