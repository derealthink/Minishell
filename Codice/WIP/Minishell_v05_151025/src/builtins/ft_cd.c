/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/13 17:54:55 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_cd_home(char **path, char **new_envp);
static void	update_and_free(t_minishell *shell, char **directory);

int	ft_cd(t_minishell *shell, char **args, char **new_envp)
{
	char	*path;
	char	*directory;

	path = NULL;
	directory = getcwd(NULL, 0);
	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
	{
		if (ft_cd_home(&path, new_envp) == 1)
		{
			free (directory);
			return (shell->last_exit_status = 1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		print_unquoted_error("cd", path, "No such file or directory");
		free (directory);
		return (shell->last_exit_status = 1);
	}
	update_and_free(shell, &directory);
	return (shell->last_exit_status = 0);
}

static int	ft_cd_home(char **path, char **new_envp)
{
	int		i;

	i = 0;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], "HOME=", 5) == 0)
		{
			*path = new_envp[i] + 5;
			break ;
		}
		i++;
	}
	if (*path == NULL)
	{
		print_simple_error("cd", "HOME not set");
		return (1);
	}
	return (0);
}

static void	update_and_free(t_minishell *shell, char **directory)
{
	update_env_var(shell, "OLDPWD", *directory);
	free (*directory);
	*directory = getcwd(NULL, 0);
	update_env_var(shell, "PWD", *directory);
	free(*directory);
}
