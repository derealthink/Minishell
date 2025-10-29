/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 17:27:24 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_struct(t_minishell *shell);

/*
int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	char		**new_envp;
	char		*line;
	int			exit_flag;

	(void)argc;
	(void)argv;
	init_minishell(&shell);		//-----part 0 init
//	if (shell.is_interactive)
//	{
//		print_logo();
//		set_terminal_mode(&shell);
//		setup_interactive_parent_signals();
//	}
//	create_env_list(&shell, envp);
//	update_shlvl(&shell);
	while (1) //----------------------------main loop
	{
		exit_flag = 0;
		g_global_signal = 0;
		new_envp = NULL;
		if (shell.is_interactive)		//----part 1 readline
		{
			line = readline("\001\033[1;32m\002minishell> \001\033[0m\002");
			if (g_global_signal == SIGINT)
				shell.last_exit_status = 130;
		}
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (shell.is_interactive)
			add_history(line);
		if (!pre_parse(line))		 //----part 2 token/lexer
		{
			printf("minishell: syntax error\n");
			free(line);
			shell.last_exit_status = 2; // typical bash syntax error code
			continue; // skip to next prompt
		}
		shell.token_list = lexer(line);
		free(line);
		find_env(&shell);
		shell.cmd_list = parser(shell.token_list, shell.cmd_list);
		if (shell.token_list)
			token_list_clear(shell.token_list);
		shell.token_list = NULL;
		new_envp = env_list_array(shell.env_list);		//-----part 3 execution
		if (shell.cmd_list && shell.cmd_list->args && shell.cmd_list->args[0])
		{
			if (ft_strcmp(shell.cmd_list->args[0], "exit") == 0)
			{
				exit_flag = 1;
				ft_exit(&shell, new_envp);
			}
		}
		if (shell.cmd_list && exit_flag == 0)
			execute_pipeline(&shell, new_envp);
		if (new_envp)
			array_clear(new_envp);
		if (shell.cmd_list)
			cmd_list_clear(shell.cmd_list);
		shell.cmd_list = NULL;
	}
	if (shell.is_interactive)		//-----fuori dal loop part 4 restore & clean
		restore_terminal(&shell);
	final_cleanup(&shell);
	return (0);
}
*/

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
	if (!shell)
		return ;

	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->cmd_list = NULL;
	shell->last_exit_status = 0;
	shell->is_interactive = shell_is_interactive();
}
/*

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;
	char		**new_envp;
	char		*line;
	int			exit_flag;

	(void)argc;
	(void)argv;
	init_minishell(&shell);		//-----part 0 init
	if (shell.is_interactive)
	{
		print_logo();
		set_terminal_mode(&shell);
		setup_interactive_parent_signals();
	}
	create_env_list(&shell, envp);
	update_shlvl(&shell);
	while (1) //----------------------------main loop
	{
		exit_flag = 0;
		g_global_signal = 0;
		new_envp = NULL;
		if (shell.is_interactive)		//----part 1 readline
		{
			line = readline("\001\033[1;32m\002minishell> \001\033[0m\002");
			if (g_global_signal == SIGINT)
				shell.last_exit_status = 130;
		}
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (shell.is_interactive)
			add_history(line);
		if (!pre_parse(line))		 //----part 2 token/lexer
		{
			printf("minishell: syntax error\n");
			free(line);
			shell.last_exit_status = 2; // typical bash syntax error code
			continue; // skip to next prompt
		}
		shell.token_list = lexer(line);
		free(line);
		find_env(&shell);
		shell.cmd_list = parser(shell.token_list, shell.cmd_list);
		if (shell.token_list)
			token_list_clear(shell.token_list);
		shell.token_list = NULL;
		new_envp = env_list_array(shell.env_list);		//-----part 3 execution
		if (shell.cmd_list && shell.cmd_list->args && shell.cmd_list->args[0])
		{
			if (ft_strcmp(shell.cmd_list->args[0], "exit") == 0)
			{
				exit_flag = 1;
				ft_exit(&shell, new_envp);
			}
		}
		if (shell.cmd_list && exit_flag == 0)
			execute_pipeline(&shell, new_envp);
		if (new_envp)
			array_clear(new_envp);
		if (shell.cmd_list)
			cmd_list_clear(shell.cmd_list);
		shell.cmd_list = NULL;
	}
	if (shell.is_interactive)		//-----fuori dal loop part 4 restore & clean
		restore_terminal(&shell);
	final_cleanup(&shell);
	return (0);
}
*/