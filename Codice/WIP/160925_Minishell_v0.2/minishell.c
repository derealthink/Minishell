/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:33:49 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 16:32:28 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	global_signal = 0;

static void	list_clear(t_table *list);
void	signal_handler(int signum);

void	set_signal_action(void);

int	main(int argc, char **argv, char **envp)
{

	t_table			*token_list;
//	t_cmd	*cmd_list = NULL;
	char			*line;

	(void)argc;
	(void)argv;
	(void)envp;

	print_logo();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			free (line);
			break ;
		}
set_signal_action();		
		
		add_history(line);
		token_list = lexer(line);
		print_tokens(token_list);
//		execute_pipeline(cmd_list, envp);
		free(line);
		if (token_list)
			list_clear(token_list);
	}
	return (0);
}

static void	list_clear(t_table *list)
{
	t_token	*ptr;
	t_token	*next;

	if (!list)
		return ;
	ptr = list->head;
	while (ptr != NULL)
	{
		next = ptr->next;
		//(free)(ptr->content);
		free (ptr);
		ptr = next;
	}
	free(list);
}

void	set_signal_action(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
		global_signal = signum;
}