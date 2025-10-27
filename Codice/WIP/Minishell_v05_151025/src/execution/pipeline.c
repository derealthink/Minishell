/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:28:03 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 13:07:30 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

static int	handle_pipe(t_minishell *shell, t_cmd *cmd_list,
				int num_cmds, char **new_envp);

int	execute_pipeline(t_minishell *shell, char **new_envp)
{
	int		num_cmds;
	t_cmd	*cmd_list;

	if (!shell->cmd_list || !new_envp)
		return (1);
	cmd_list = shell->cmd_list;
	num_cmds = list_size(cmd_list);
	if (num_cmds == 0)
		return (shell->last_exit_status);
	if (num_cmds == 1)
		return (single_command(shell, cmd_list, new_envp));
	return (handle_pipe(shell, cmd_list, num_cmds, new_envp));
}

static int	handle_pipe(t_minishell *shell, t_cmd *cmd_list,
				int num_cmds, char **new_envp)
{
	struct sigaction	sa_original;
	int					*pipes;
	int					status;

	(void)cmd_list;
	pipes = initialize_pipes(num_cmds);
	if (!pipes)
		return (1);
	sigaction(SIGINT, NULL, &sa_original);
	set_signal_handler(SIGINT, SIG_IGN, 0);
	status = execute_pipe_children(shell, pipes, num_cmds, new_envp);
	sigaction(SIGINT, &sa_original, NULL);
	if (status != 0)
		return (status);
	close_pipes_and_wait(shell, pipes, num_cmds);
	return (shell->last_exit_status);
}

/*
static int	single_command(t_minishell *shell, t_cmd *cmd_list, char **new_envp)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa_original;

	status = 0;
	if (is_parent_builtin(cmd_list->args[0]))
	{
		shell->last_exit_status = execute_builtin(shell, cmd_list, &new_envp);
		return (shell->last_exit_status);
	}
	sigaction(SIGINT, NULL, &sa_original);
	set_signal_handler(SIGINT, SIG_IGN, 0);
	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		if (check_redirection(cmd_list) == -1)
			exit(1);
		exe_child(shell, cmd_list, new_envp);
	}
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &sa_original, NULL);
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	else
		shell->last_exit_status = 1;
	return (shell->last_exit_status);

static int	handle_pipe(t_minishell *shell, t_cmd *cmd_list,
				int num_cmds, char **new_envp)
{
	struct sigaction	sa_original;
	t_cmd				*current;
	pid_t				pid;
	int					*pipes;
	int					i;

	pipes = initialize_pipes(num_cmds);
	if (!pipes)
		return (1);
	current = cmd_list;
	i = 0;
	sigaction(SIGINT, NULL, &sa_original);
	set_signal_handler(SIGINT, SIG_IGN, 0);
	while (current)
	{
		pid = fork();
		if (pid == -1)
			return (fork_failed(pipes, num_cmds));
		if (pid == 0)
		{
			fork_set_child(current, pipes, num_cmds, i);
			exe_child(shell, current, new_envp);
		}
		i++;
		current = current->next;
	}
	sigaction(SIGINT, &sa_original, NULL);
	close_pipes_and_wait(shell, pipes, num_cmds);
	return (shell->last_exit_status);
}
*/