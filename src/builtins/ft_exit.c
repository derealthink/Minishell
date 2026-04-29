/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:13:58 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 16:45:21 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	handle_non_numeric_exit(t_minishell *shell, char **args,
				char **new_envp);
static int	handle_exit_args(t_minishell *shell, char **args, char **new_envp);
static int	ft_exit_status(t_minishell *shell, char **args);
static void	cleanup_and_exit(t_minishell *shell, char **new_envp);

int	ft_exit(t_minishell *shell, char **new_envp)
{
	char	**args;
	int		i;

	args = shell->cmd_list->args;
	if (!args || !*args)
		return (-1);
	if (ft_strcmp(args[0], "exit") != 0)
		return (-1);
	if (shell->is_interactive)
		write(STDERR_FILENO, "exit\n", 5);
	if (args[1] && ft_is_numeric(args[1]) == 0)
		return (handle_non_numeric_exit(shell, args, new_envp));
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		print_simple_error("exit", "too many arguments");
		return (shell->last_exit_status = 1);
	}
	if (args[1])
		return (handle_exit_args(shell, args, new_envp));
	restore_terminal(shell);
	cleanup_and_exit(shell, new_envp);
	return (0);
}

static void	cleanup_and_exit(t_minishell *shell, char **new_envp)
{
	if (new_envp)
		array_clear(new_envp);
	final_cleanup(shell);
	exit(shell->last_exit_status);
}

static int	handle_non_numeric_exit(t_minishell *shell, char **args,
				char **new_envp)
{
	print_unquoted_error("exit", args[1], "numeric argument required");
	shell->last_exit_status = 2;
	restore_terminal(shell);
	cleanup_and_exit(shell, new_envp);
	return (2);
}

static int	handle_exit_args(t_minishell *shell, char **args, char **new_envp)
{
	ft_exit_status(shell, args);
	cleanup_and_exit(shell, new_envp);
	return (0);
}

static int	ft_exit_status(t_minishell *shell, char **args)
{
	long long	exit_val;

	if (ft_atol_limit_check(args[1], &exit_val) != 0)
	{
		print_unquoted_error("exit", args[1], "numeric argument required");
		shell->last_exit_status = 2;
		return (1);
	}
	shell->last_exit_status = (unsigned char)exit_val;
	return (0);
}
