/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/10/03 18:43:32 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_table	*token_list;
	t_cmd	*cmd_list;
	char	*line;

	(void)argc;
	(void)argv;
	print_logo();
	set_signal_action();
	set_terminal_mode();
	while (1)
	{
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
		{
			rl_clear_history();
//			restore_original_terminal();
			break ;
		}
		add_history(line);
		token_list = lexer(line);
		free(line);
		cmd_list = NULL;
//print_tokens(token_list);
		cmd_list = parser(token_list, cmd_list);
		if (token_list)
			token_list_clear(token_list);
//print_cmd_list(cmd_list);
		ft_exit(cmd_list, envp);
		execute_pipeline(cmd_list, envp);
		if (cmd_list)
			cmd_list_clear(cmd_list);
	}
	return (0);
}
