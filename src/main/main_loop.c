/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/11/03 13:12:21 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_input(t_minishell *shell);
static void	execution(t_minishell *shell);
static void	process_tokens(t_minishell *shell, char *line);
static bool	parse_input(t_minishell *shell, char *line);

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
		shell->last_exit_status = 2;
		return (false);
	}
	process_tokens(shell, line);
	return (true);
}
