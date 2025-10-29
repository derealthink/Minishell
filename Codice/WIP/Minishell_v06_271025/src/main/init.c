/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 18:13:26 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_struct(t_minishell *shell);

void	init_minishell(t_minishell *shell, char **envp)
{
	init_shell_struct(shell);
	if (shell->is_interactive)
	{
		print_logo();
		set_terminal_mode(shell);
		setup_interactive_parent_signals();
	}
	create_env_list(shell, envp);
	update_shlvl(shell);
}

static void	init_shell_struct(t_minishell *shell)
{
	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->cmd_list = NULL;
	shell->last_exit_status = 0;
	shell->is_interactive = shell_is_interactive();
}
