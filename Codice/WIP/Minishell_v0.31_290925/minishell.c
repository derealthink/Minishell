/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/10/06 16:04:29 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_minishell(t_minishell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	char		**new_envp;
	char		*line;

	(void)argc;
	(void)argv;
	init_minishell(&shell);
	print_logo();
	set_signal_action();
	set_terminal_mode();
	create_env_list(&shell, envp);
	while (1)
	{
		new_envp = NULL;
		line = readline("minishell> ");
		if(global_signal == SIGINT)  // definire prima se interactive o non interactive
		{
			global_signal = 0;
			rl_replace_line("", 0);
			rl_on_new_line();
			write(STDOUT_FILENO, "\n", 1);
			rl_redisplay();
			continue ;
		}	
		if (!line)
			break ;
		add_history(line);
		shell.token_list = lexer(line);
		free(line);
//print_tokens(token_list);
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
			args_clear(new_envp);
		if (shell.cmd_list)
			cmd_list_clear(shell.cmd_list);
		shell.cmd_list = NULL;
	}
	final_cleanup(&shell);
//	restore_original_terminal();
	return (0);
}

static void	init_minishell(t_minishell *shell)
{
	if (!shell)
		return ;

	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->cmd_list = NULL;
	shell->last_exit_status = 0;
	shell->is_interactive = 0;
}