/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:32 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 15:03:46 by aielo            ###   ########.fr       */
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
int		pre_parse(char *str);
int		tokenizer_dquotes(char *str, t_table *list);
int		tokenizer_squotes(char *str, t_table *list);
int		tokenizer_norm(char *str, t_table *list);
t_token	*sort_redir(t_token *token, t_cmd *table);
t_token	*sort_app(t_token *token, t_cmd *table);
t_token	*sort_herd(t_token *token, t_cmd *table);
void	args_to_cmd(t_cmd *cmd, t_token *start);

#endif
