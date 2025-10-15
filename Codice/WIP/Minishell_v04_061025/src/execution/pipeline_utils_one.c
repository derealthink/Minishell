/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:28:03 by aielo             #+#    #+#             */
/*   Updated: 2025/10/13 17:03:33 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

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

	if (cmd_list->input_file || cmd_list->delimiter)
	{
		fd = handle_redirect_in(cmd_list);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (i > 0)
		dup2(pipes[(i - 1) * 2], STDIN_FILENO);
	if (cmd_list->output_file)
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

void	parent_wait(t_minishell *shell, int num_cmds)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		wait(&status);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		i++;
	}
}
