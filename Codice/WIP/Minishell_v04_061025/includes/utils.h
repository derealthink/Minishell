/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:44 by aielo             #+#    #+#             */
/*   Updated: 2025/10/06 16:05:51 by aielo            ###   ########.fr       */
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

void	final_cleanup(t_minishell *shell);
void	token_list_clear(t_table *list);
void	cmd_list_clear(t_cmd *cmd_list);
void	args_clear(char **args);
void	env_list_clear(t_env_list *env_list);
//void	new_envp_clear(char **new_envp);

#endif