/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/26 18:02:50 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_and_free(t_minishell *shell, char **directory);

int	ft_cd(t_minishell *shell, char **args, char **new_envp)
{
	char	*path;
	char	*old_directory;
	int		i;
	int		free_path_flag;

	old_directory = getcwd(NULL, 0);
	free_path_flag = 0;
	path = args[1];
	i = cd_special_cases(&path, args, new_envp);
	if (i == 1)
		return (free(old_directory), shell->last_exit_status = 1);
	else if (i == 2)
		free_path_flag = 1;
	if (chdir(path) != 0)
	{
		print_unquoted_error("cd", path, "No such file or directory");
		if (free_path_flag)
			free(path);
		return (free(old_directory), shell->last_exit_status = 1);
	}
	update_and_free(shell, &old_directory);
	if (free_path_flag)
		free(path);
	return (shell->last_exit_status = 0);
}

static void	update_and_free(t_minishell *shell, char **directory)
{
	update_env_var(shell, "OLDPWD", *directory);
	free (*directory);
	*directory = getcwd(NULL, 0);
	update_env_var(shell, "PWD", *directory);
	free(*directory);
}

/*
int	ft_cd(t_minishell *shell, char **args, char **new_envp)
{
	char	*path;
	char	*old_directory;
	int		i;

	path = NULL;
	old_directory = getcwd(NULL, 0);
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		print_simple_error("cd", "too many arguments");
		return (free(old_directory), shell->last_exit_status = 1);
	}
	path = args[1];
	if (cd_special_cases(&path, args, new_envp) == 1)
		return (free(old_directory), shell->last_exit_status = 1);
	if (chdir(path) != 0)
	{
		print_unquoted_error("cd", path, "No such file or directory");
		return (free(old_directory), shell->last_exit_status = 1);
	}
	update_and_free(shell, &old_directory);
	return (shell->last_exit_status = 0);
}
*/
