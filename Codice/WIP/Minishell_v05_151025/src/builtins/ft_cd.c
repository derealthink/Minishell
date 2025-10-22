/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/22 18:34:52 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	cd_special_cases(char **path, char **args, char **new_envp);
static int	cd_home(char **path, char **new_envp);
static int	cd_tilde(char **path, char **args, char **new_envp);
static int	cd_previous(char **path, char **new_envp);
static int	cd_users(char **path, char **new_envp);
static void	update_and_free(t_minishell *shell, char **directory);

int	ft_cd(t_minishell *shell, char **args, char **new_envp)
{
	char	*path;
	char	*old_directory;
	int		i;
	int		free_path_flag;

	path = NULL;
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

static int	cd_special_cases(char **path, char **args, char **new_envp)
{
	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
		return (cd_home(path, new_envp));
	else if ((args[1][0] == '~' && args[1][1] == '/'))
		return (cd_tilde(path, args, new_envp));
	else if (args[1][0] == '-' && args[1][1] == '\0')
		return (cd_previous(path, new_envp));
	else if (ft_strncmp(args[1], "/Users", 6) == 0)
		return (cd_users(path, new_envp));
	return (0);
}

static int	cd_home(char **path, char **new_envp)
{
	int	i;

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

static int	cd_tilde(char **path, char **args, char **new_envp)
{
	char	*tmp_home;
	char	*rest_path;
	int		i;

	tmp_home = NULL;
	i = 0;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], "HOME=", 5) == 0)
		{
			tmp_home = new_envp[i] + 5;
			break ;
		}
		i++;
	}
	if (tmp_home == NULL)
	{
		print_simple_error("cd", "HOME not set");
		return (1);
	}
	rest_path = ft_substr(args[1], 1, ft_strlen(args[1]) - 1);
	if (!rest_path)
		return (1);
	*path = ft_strjoin(tmp_home, rest_path);
	free(rest_path);
	if (!path)
		return (1);
	return (2);
}

static int	cd_previous(char **path, char **new_envp)
{
	int	i;

	i = 0;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], "OLDPWD=", 7) == 0)
		{
			*path = new_envp[i] + 7;
			break ;
		}
		i++;
	}
	if (*path == NULL)
	{
		print_simple_error("cd", "OLDPWD not set");
		return (1);
	}
	return (0);
}

static int	cd_users(char **path, char **new_envp)
{
	int	i;

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
		print_simple_error("cd", "/Users: No such file or directory");
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
