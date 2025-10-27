/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/24 14:01:43 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_minishell *shell, char **new_envp)
{
	char	*directory;
	int		i;

	directory = NULL;
	i = 0;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], "PWD=", 4) == 0)
		{
			directory = new_envp[i] + 4;
			printf("%s\n", directory);
			break ;
		}
		i++;
	}
	if (!directory)
	{
		perror("pwd: ");
		return (1);
	}
	return (shell->last_exit_status = 0);
}
