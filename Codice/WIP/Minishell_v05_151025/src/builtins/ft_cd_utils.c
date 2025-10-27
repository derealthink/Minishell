/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 12:07:05 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	cd_home(char **path, char **new_envp);
static int	cd_tilde(char **path, char **args, char **new_envp);
static int	cd_previous(char **path, char **new_envp);
static int	find_env_value(char **path, char **new_envp, char *to_find);

int	cd_special_cases(char **path, char **args, char **new_envp)
{
	int	i;
	int	free_flag;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		print_simple_error("cd", "too many arguments");
		return (1);
	}
	if (args[1] == NULL || (args[1][0] == '~' && args[1][1] == '\0'))
		return (cd_home(path, new_envp));
	else if ((args[1][0] == '~' && args[1][1] == '/'))
	{
		if (cd_tilde(path, args, new_envp) == 0)
			free_flag = 2;
		else
			free_flag = 1;
		return (free_flag);
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
		return (cd_previous(path, new_envp));
	return (0);
}

static int	cd_home(char **path, char **new_envp)
{
	int	found;

	found = find_env_value(path, new_envp, "HOME=");
	if (found == 0)
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
	int		found;

	tmp_home = NULL;
	found = find_env_value(&tmp_home, new_envp, "HOME=");
	if (found == 0)
	{
		print_simple_error("cd", "HOME not set");
		return (1);
	}
	rest_path = ft_substr(args[1], 1, ft_strlen(args[1]) - 1);
	if (!rest_path)
		return (1);
	*path = ft_strjoin(tmp_home, rest_path);
	free(rest_path);
	if (!*path)
		return (1);
	return (0);
}

static int	cd_previous(char **path, char **new_envp)
{
	int	found;

	found = find_env_value(path, new_envp, "OLDPWD=");
	if (found == 0)
	{
		print_simple_error("cd", "OLDPWD not set");
		return (1);
	}
	return (0);
}

static int	find_env_value(char **value_ptr, char **new_envp, char *to_find)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], to_find, ft_strlen(to_find)) == 0)
		{
			*value_ptr = new_envp[i] + ft_strlen(to_find);
			found = 1;
			break ;
		}
		i++;
	}
	return (found);
}
