/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:28:03 by aielo             #+#    #+#             */
/*   Updated: 2025/10/21 16:15:00 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

int	*initialize_pipes(int num_cmds)
{
	int	*pipes;

	pipes = malloc(sizeof(int) * (num_cmds - 1) * 2);
	if (!pipes || create_pipes(num_cmds, pipes))
	{
		free(pipes);
		return (NULL);
	}
	return (pipes);
}

int	fork_failed(int *pipes, int num_cmds)
{
	close_all_pipes(pipes, (num_cmds - 1) * 2);
	free(pipes);
	return (1);
}

void	close_pipes_and_wait(t_minishell *shell, int *pipes, int num_cmds)
{
	close_all_pipes(pipes, (num_cmds - 1) * 2);
	parent_wait(shell, num_cmds);
	free(pipes);
}

void	fork_set_child(t_cmd *current, int *pipes, int num_cmds, int i)
{
	setup_child_signals();
	setup_in_out(current, pipes, i, num_cmds);
	close_all_pipes(pipes, (num_cmds - 1) * 2);
}
