/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 19:55:49 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_input(t_minishell *shell);
static void	execution(t_minishell *shell);

/*void	minishell_main_loop(t_minishell	*shell)
{
	char		*line;

	while (1)
	{
		g_global_signal = 0;
		line = read_input(shell);
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (shell->is_interactive)
			add_history(line);
		if (!pre_parse(line))	//----part 2 token/lexer
		{
			printf("minishell: syntax error\n");
			free(line);
			shell->last_exit_status = 2;	// typical bash syntax error code
			continue ;	// skip to next prompt
		}
		shell->token_list = lexer(line);
		free(line);
		find_env(shell);
		shell->cmd_list = parser(shell->token_list, shell->cmd_list);
		if (shell->token_list)
			token_list_clear(shell->token_list);
		shell->token_list = NULL;	//-----end part 2
		execution(shell);
	}
}*/

static char	*read_input(t_minishell *shell)
{
	char	*line;

	if (shell->is_interactive)
	{
		line = readline("\001\033[1;32m\002minishell> \001\033[0m\002");
		if (g_global_signal == SIGINT)
			shell->last_exit_status = 130;
	}
	else
		line = get_next_line(STDIN_FILENO);
	return (line);
}

static void	execution(t_minishell *shell)
{
	char		**new_envp;
	int			exit_flag;

	exit_flag = 0;
	new_envp = NULL;
	new_envp = env_list_array(shell->env_list);
	if (shell->cmd_list && shell->cmd_list->args && shell->cmd_list->args[0])
	{
		if (ft_strcmp(shell->cmd_list->args[0], "exit") == 0)
		{
			exit_flag = 1;
			ft_exit(shell, new_envp);
		}
	}
	if (shell->cmd_list && exit_flag == 0)
		execute_pipeline(shell, new_envp);
	if (new_envp)
		array_clear(new_envp);
	if (shell->cmd_list)
		cmd_list_clear(shell->cmd_list);
	shell->cmd_list = NULL;
}

static void	process_tokens(t_minishell *shell, char *line)
{
	shell->token_list = lexer(line);
	free(line);
	find_env(shell);
	shell->cmd_list = parser(shell->token_list, shell->cmd_list);
	if (shell->token_list)
		token_list_clear(shell->token_list);
	shell->token_list = NULL;
}

static bool	parse_input(t_minishell *shell, char *line)
{
	if (!pre_parse(line))
	{
		printf("minishell: syntax error\n");
		free(line);
		shell->last_exit_status = 2; // typical bash syntax error code
		return (false); // skip to next prompt
	}
	process_tokens(shell, line);
	return (true);
}

void	minishell_main_loop(t_minishell *shell)
{
	char	*line;

	while (1)
	{
		g_global_signal = 0;
		line = read_input(shell);
		if (!line)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (shell->is_interactive)
			add_history(line);
		if (!parse_input(shell, line))
			continue ;
		execution(shell);
	}
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