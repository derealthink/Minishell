/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:13:58 by aielo             #+#    #+#             */
/*   Updated: 2025/10/15 13:11:00 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	handle_exit_args(t_minishell *shell, char **args, char **new_envp);
static int	ft_exit_status(t_minishell *shell, char **args);
static void	cleanup_and_exit(t_minishell *shell, char **new_envp);

int	ft_exit(t_minishell *shell, char **new_envp)
{
	char	**args;
	int		i;

	args = shell->cmd_list->args;
	if (ft_strcmp(args[0], "exit") != 0)
		return (-1);
	write(STDERR_FILENO, "exit\n", 5);
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		print_simple_error("exit", "too many arguments");
		shell->last_exit_status = 1;
		return (shell->last_exit_status);
	}
	if (args[1])
		return (handle_exit_args(shell, args, new_envp));
	cleanup_and_exit(shell, new_envp);
	return (0);
}

static void cleanup_and_exit(t_minishell *shell, char **new_envp)
{
	if (new_envp)
		array_clear(new_envp);
	final_cleanup(shell);
	exit(shell->last_exit_status);
}

static int handle_exit_args(t_minishell *shell, char **args, char **new_envp)
{
	if (ft_exit_status(shell, args) != 0)
		cleanup_and_exit(shell, new_envp);
	cleanup_and_exit(shell, new_envp);
	return (0);
}

static int	ft_exit_status(t_minishell *shell, char **args)
{
	long long exit_val;

	if (ft_is_numeric(args[1]) == 0)
	{
		print_unquoted_error("exit", args[1], "numeric argument required");
		shell->last_exit_status = 2;
		return (1);
	}
	if (ft_atol_limit_check(args[1], &exit_val) != 0)
	{
		print_unquoted_error("exit", args[1], "numeric argument required");
		shell->last_exit_status = 2;
		return (1);
	}
	shell->last_exit_status = (unsigned char)exit_val;
	return (0);
}
