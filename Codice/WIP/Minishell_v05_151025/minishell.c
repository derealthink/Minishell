/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/10/21 19:45:44 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_minishell(t_minishell *shell);
/*
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	char		**new_envp;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&shell);
	print_logo();
	set_terminal_mode(&shell);
	setup_interactive_parent_signals();
	create_env_list(&shell, envp);
	update_shlvl(&shell);
	while (1)
	{
		g_global_signal = 0;
		new_envp = NULL;
		line = readline("\033[32mminishell> \033[0m");
		if (g_global_signal == SIGINT)
		{
			g_global_signal = 0;
			continue ;
		}
		if (!line)
			break ;
//else if (parse_error(shell, line)) shell per exit status
//		add_history(line);
//		free(line);
//		else if (line && *line != '\0')
		if (line && *line != '\0')
		{
			add_history(line);
			shell.token_list = lexer(line);
			free(line);
//print_tokens(shell.token_list);
			shell.cmd_list = parser(shell.token_list, shell.cmd_list);
			if (shell.token_list)
				token_list_clear(shell.token_list);
			shell.token_list = NULL;
//print_cmd_list(shell.cmd_list);
			new_envp = env_list_array(shell.env_list);
			if(shell.cmd_list)
			{
				if (ft_exit(&shell, new_envp) == -1)
					execute_pipeline(&shell, new_envp);
			}
			if (new_envp)
				array_clear(new_envp);
			if (shell.cmd_list)
				cmd_list_clear(shell.cmd_list);
			shell.cmd_list = NULL;
		}
	}
	restore_terminal(&shell);
	final_cleanup(&shell);
	return (0);
}
*/
static void	init_minishell(t_minishell *shell)
{
	if (!shell)
		return ;

	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->cmd_list = NULL;
	shell->last_exit_status = 0;
	shell->is_interactive = shell_is_interactive();
}


int main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	char		**new_envp;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&shell);
//	print_logo();
	if (shell.is_interactive)
	{
		set_terminal_mode(&shell);
		setup_interactive_parent_signals();
	}
	else
	{
		set_signal_handler(SIGINT, SIG_DFL, 0);
		set_signal_handler(SIGQUIT, SIG_DFL, 0);
	}
	create_env_list(&shell, envp);
	update_shlvl(&shell);
	while (1)
	{
		g_global_signal = 0;
		new_envp = NULL;
		if (shell.is_interactive)
		{
			line = readline("\033[32mminishell> \033[0m");
			if (g_global_signal == SIGINT)
            {
                shell.last_exit_status = 130; // Set exit status for Ctrl-C
                if (line)
                    free(line);
                continue;
            }
			if (!line)
				break;
		}
		else
		{
			line = get_next_line(STDIN_FILENO);
			if (!line)
				break;
		}
		if (*line == '\0') // Empty line, just Enter pressed
		{
			free(line);
			continue;
		}
		if (line)
		{
			if (shell.is_interactive)
				add_history(line);
			shell.token_list = lexer(line);
			free(line);
			find_env(&shell);
			shell.cmd_list = parser(shell.token_list, shell.cmd_list);
			if (shell.token_list)
				token_list_clear(shell.token_list);
			shell.token_list = NULL;
			new_envp = env_list_array(shell.env_list);
			if(shell.cmd_list)
			{
				if (ft_exit(&shell, new_envp) == -1)
					execute_pipeline(&shell, new_envp);
			}
			if (new_envp)
				array_clear(new_envp);
			if (shell.cmd_list)
				cmd_list_clear(shell.cmd_list);
			shell.cmd_list = NULL;
		}
	}
	if (shell.is_interactive)
		restore_terminal(&shell);
	final_cleanup(&shell); //aggiornare clear_history con if(shell.is_interactive)
	return (0);
}

