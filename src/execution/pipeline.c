/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:28:03 by aielo             #+#    #+#             */
/*   Updated: 2025/11/03 13:09:54 by aielo            ###   ########.fr       */
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
