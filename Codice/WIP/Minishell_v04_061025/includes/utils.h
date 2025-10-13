/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:44 by aielo             #+#    #+#             */
/*   Updated: 2025/10/09 22:18:42 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include "types.h"
# include "libft.h"

void	print_logo(void);

void	print_simple_error(char *cmd, char *text);
void	print_quoted_error(char *cmd, char *arg, char *text);
void	print_unquoted_error(char *cmd, char *arg, char *text);
void	print_quoted_exe_error(char *cmd, char *arg, char *text);
void	print_unquoted_exe_error(char *cmd, char *text);

void	array_clear(char **args);
void	final_cleanup(t_minishell *shell);
void	token_list_clear(t_table *list);
void	cmd_list_clear(t_cmd *cmd_list);
void	env_list_clear(t_env_list *env_list);

int		list_size(void *lst);

#endif