/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:13:58 by aielo             #+#    #+#             */
/*   Updated: 2025/10/09 21:45:58 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exit(t_minishell *shell, char **new_envp)
{
	char	**args;
	int		i;

	i = 0;
	args = shell->cmd_list->args;
	if (ft_strcmp(args[0], "exit") == 0)
	{
		while (args[i])
			i++;
		if (i > 2)
		{
			print_simple_error("exit", "too many arguments");
			shell->last_exit_status = 1;
			return (shell->last_exit_status);
		}
		if (args[1])
		{
			i = 0;
			while (args[1][i])
			{
				if (args[1][i] < '0' || args[1][i] > '9')
				{
					print_unquoted_error("exit", args[1],
						"numeric argument required");
					shell->last_exit_status = 255;
					return (shell->last_exit_status);
				}
				i++;
			}
			shell->last_exit_status = atoi(args[1]);
		}
		if (new_envp)
			array_clear(new_envp);
		final_cleanup(shell);
		exit (shell->last_exit_status);
	}
	return (-1);
}

/*
exit hello	bash: exit: hello: numeric argument required	255
exit 1 2	bash: exit: too many arguments	1 (The shell does not exit)
*/

/*
int	exit_status()
{
	printf("%d\n", WEXITSTATUS(status));
	
	exit(last_command_status);
}*/

// https://linuxize.com/post/bash-exit/