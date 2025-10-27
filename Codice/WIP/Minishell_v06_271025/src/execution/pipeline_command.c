/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:28:03 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 14:37:11 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

static int	execute_single_cmd(t_minishell *shell, t_cmd *cmd_list,
				char **new_envp);
static int	check_redirection(t_cmd *cmd_list);
static int	exe_child(t_minishell *shell, t_cmd *cmd_list, char **new_envp);

int	single_command(t_minishell *shell, t_cmd *cmd_list,	char **new_envp)
{
/*	if (cmd_list->args[0] == NULL)
	{
		if (cmd_list->input_file || cmd_list->delimiter || cmd_list->output_file)
		{
			if (check_redirection(cmd_list) == 0)
				return (shell->last_exit_status = 0); 
			return (shell->last_exit_status = 1); 
		}
		return (shell->last_exit_status = 0);
	}*/
	if (is_parent_builtin(cmd_list->args[0]))
	{
		shell->last_exit_status = execute_builtin(shell, cmd_list, &new_envp);
		return (shell->last_exit_status);
	}
	return (execute_single_cmd(shell, cmd_list, new_envp));
}

static int	execute_single_cmd(t_minishell *shell, t_cmd *cmd_list,
				char **new_envp)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa_original;

	status = 0;
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
}

int	execute_pipe_children(t_minishell *shell, int *pipes, int num_cmds,
							char **new_envp)
{
	t_cmd	*current;
	pid_t	pid;
	int		i;

	current = shell->cmd_list;
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
	return (0);
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
