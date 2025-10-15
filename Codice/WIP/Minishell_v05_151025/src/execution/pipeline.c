/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:28:03 by aielo             #+#    #+#             */
/*   Updated: 2025/10/15 18:08:36 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

static int	single_command(t_minishell *shell,
				t_cmd *cmd_list, char **new_envp);
static int	handle_pipe(t_minishell *shell, t_cmd *cmd_list,
				int num_cmds, char **new_envp);
static int	check_redirection(t_cmd *cmd_list);
static int	exe_child(t_minishell *shell, t_cmd *cmd_list, char **new_envp);

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
// se $ modificare/creare una nuova cmd_list con expansion da passare a builtins e execve
// name=value senza export??
	if (num_cmds == 1)
		return (single_command(shell, cmd_list, new_envp));
	return (handle_pipe(shell, cmd_list, num_cmds, new_envp));
}

static int	single_command(t_minishell *shell, t_cmd *cmd_list, char **new_envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (is_parent_builtin(cmd_list->args[0]))
	{
		shell->last_exit_status = execute_builtin(shell, cmd_list, &new_envp);
		return (shell->last_exit_status);
	}
	pid = fork();
	if (pid == 0)
	{
		reset_signals_child();
		if (check_redirection(cmd_list) == -1)
			exit(1);
		exe_child(shell, cmd_list, new_envp);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	else
		shell->last_exit_status = 1;
	return (shell->last_exit_status);
}

static int	handle_pipe(t_minishell *shell, t_cmd *cmd_list,
				int num_cmds, char **new_envp)
{
	t_cmd	*current;
	pid_t	pid;
	int		*pipes;
	int		i;

	pipes = initialize_pipes(num_cmds);
	if (!pipes)
		return (1);
	current = cmd_list;
	i = 0;
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
	close_pipes_and_wait(shell, pipes, num_cmds);
	return (shell->last_exit_status);
}

static int	check_redirection(t_cmd *cmd_list)
{
	int	fd;

	if (cmd_list->input_file || cmd_list->delimiter)
	{
		fd = handle_redirect_in(cmd_list);
		if (fd == -1)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd_list->output_file)
	{
		fd = handle_redirect_out(cmd_list);
		if (fd == -1)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static int	exe_child(t_minishell *shell, t_cmd *cmd_list, char **new_envp)
{
	int	status;

	status = shell->last_exit_status;
	if (is_child_builtin(cmd_list->args[0]))
	{
		status = execute_builtin(shell, cmd_list, &new_envp);
		exit(status);
	}
	else
	{
		execute_cmd(cmd_list->args[0], cmd_list->args, new_envp);
		exit(status = 127);
	}
}
