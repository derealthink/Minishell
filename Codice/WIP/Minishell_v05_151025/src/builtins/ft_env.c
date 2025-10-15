/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/15 13:09:14 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_minishell *shell, char **new_envp)
{
	char	**args;
	int		i;

	i = 0;
	args = shell->cmd_list->args;
	while (args[i])
		i++;
	if (i > 1)
	{
		print_quoted_exe_error("env", args[1], "No such file or directory");
		shell->last_exit_status = 127;
		return (shell->last_exit_status);
	}
	i = 0;
	while (new_envp[i])
	{
		printf("%s\n", new_envp[i]);
		i++;
	}
	return (0);
}

// trova il valore della envp (ex $HOME)
int	env_variable(char **args, char **new_envp)
{
	int		i;
	char	*path_value;

	i = 0;
	path_value = NULL;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], args[1], ft_strlen(args[1])) == 0)
		{
			path_value = new_envp[i] + ft_strlen(args[1]);
			break ;
		}
		i++;
	}
	if (!path_value)
		return (0);
	printf("%s\n", path_value);
	return (0);
}
