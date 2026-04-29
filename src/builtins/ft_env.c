/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 11:39:25 by aielo            ###   ########.fr       */
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
		return (shell->last_exit_status = 127);
	}
	i = 0;
	while (new_envp[i])
	{
		printf("%s\n", new_envp[i]);
		i++;
	}
	return (0);
}
