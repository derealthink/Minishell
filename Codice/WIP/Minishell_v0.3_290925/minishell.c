/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/09/30 11:47:41 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_table	*token_list;
	t_cmd	*cmd_list = NULL;
	char	*line;

	(void)argc;
	(void)argv;
	print_logo();
	while (1)
	{
		line = readline("minishell> ");
		if (!line || global_signal != 0)
		{
			free (line);
			global_signal = 0;
			break ;
		}
//set_signal_action();		
		add_history(line);
		token_list = lexer(line);
		init_cmd(cmd_list);
		cmd_list = parser(token_list, cmd_list);
		print_cmd_list(cmd_list);
//print_tokens(token_list);
		execute_pipeline(cmd_list, envp);
		free(line);
		if (token_list)
			token_list_clear(token_list);
	}
	return (0);
}
