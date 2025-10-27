/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:32 by aielo             #+#    #+#             */
/*   Updated: 2025/10/27 11:22:45 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "types.h"
# include "utils.h"

char	**ftt_split(char *str, char del);
int		is_space(char c);
t_token	*new_token(char *value);
t_table	*init_list(void);
int		is_quotes(char c);
t_table	*lexer(char *str);
char	*str_div(char *str);
char	*str_div_q(char *str);
int		process_token_at_position(char *str, int pos,
			t_state state, t_table *list);
void	print_tokens(t_table *list);//temp
void	print_cmd_list(t_cmd *cmd_list);//temp
int		is_pipe(char *str);
int		is_rout(char *str);
int		is_rin(char *str);
int		is_append(char *str);
int		is_heredoc(char *str);
int		is_env(char *str);
t_cmd	*new_cmd(t_cmd *prev);
void	init_cmd(t_cmd *cmd);
t_cmd	*parser(t_table *list, t_cmd *table);
int		is_env(char *str);

#endif

/*
	Your parser would be responsible for creating and populating this linked list. 
	Each t_cmd node represents a single command and holds its arguments, 
	along with file descriptors for any I/O redirections. 
	The input_fd and output_fd would be set to STDIN_FILENO and STDOUT_FILENO by default 
	and updated if redirections are found.

	// Your parser should populate:
	cmd->path = "ls";           // or full path
	cmd->args = {"ls", "-la", NULL};  // including command as args[0]
*/