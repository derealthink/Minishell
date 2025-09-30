/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:28:03 by aielo             #+#    #+#             */
/*   Updated: 2025/09/30 16:36:13 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

int	execute_pipeline(t_cmd *cmd_list, char **envp)
{
	int		i;
	int		fd;
	int		num_cmds;
	int		*pipes;
	int		status;
	t_cmd	*current;
	pid_t	pid;

	if (!cmd_list || !envp)
		return (1);
	current = cmd_list;
	num_cmds = 0;
	while (current)
	{
		num_cmds++;
		current = current->next;
	}
	if (num_cmds == 1 && is_parent_builtin(cmd_list->args[0]))
	{
		status = execute_builtin(cmd_list, &envp);
		return(status);
	}
	if (num_cmds == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			reset_signals_child();
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
			if (is_child_builtin(cmd_list->args[0]))
			{
				status = execute_builtin(cmd_list, &envp);
				exit(status);
			}
			else
			{
				execute_cmd(cmd_list->args[0], cmd_list->args, envp);
				exit(127);  //127 - command not found
			}
		}
		waitpid(pid, NULL, 0);
		return (0);
	}
	pipes = malloc(sizeof(int) * (num_cmds - 1) * 2);
	if (!pipes || create_pipes(num_cmds, pipes))
	{
		if (pipes)
			free(pipes);
		return (1);
	}
	current = cmd_list;
	i = 0;
	while (current)
	{
		pid = fork();
		if (pid == -1)
		{
			close_all_pipes(pipes, (num_cmds - 1) * 2);
			free(pipes);
			return (1);
		}
		if (pid == 0)
		{
			reset_signals_child();
			setup_in_out(current, pipes, i, num_cmds);
			if (is_child_builtin(current->args[0]))
			{
				status = execute_builtin(current, &envp);
				exit(status);
			}
			else
			{
				execute_cmd(current->args[0], current->args, envp);
				exit(127);
			}
		}
		i++;
		current = current->next;
	}
	close_all_pipes(pipes, (num_cmds - 1) * 2);
	parent_wait(num_cmds);
	free(pipes);
	return (0);
}

int	create_pipes(int num_cmds, int *pipes)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(&pipes[i * 2]) == -1)
		{
			j = 0;
			while (j < i)
			{
				close(pipes[j * 2]);
				close(pipes[j * 2 + 1]);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	setup_in_out(t_cmd *cmd_list, int *pipes, int i, int num_cmds)
{
	int	fd;
	
	if (!cmd_list->input_file || !cmd_list->delimiter)
	{
		fd = handle_redirect_in(cmd_list);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (i > 0)
		dup2(pipes[(i - 1) * 2], STDIN_FILENO);
	if (!cmd_list->output_file)
	{
		fd = handle_redirect_out(cmd_list);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (i < num_cmds - 1)
		dup2(pipes[i * 2 + 1], STDOUT_FILENO);
	close_all_pipes(pipes, (num_cmds - 1) * 2);
}

void	close_all_pipes(int *pipes, int num_fds)
{
	int	i;

	i = 0;
	while (i < num_fds)
	{
		close(pipes[i]);
		i++;
	}
}

void	parent_wait(int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		wait(NULL); // wait(&status); ??
		i++;
	}
}
