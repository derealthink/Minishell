/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:16:26 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 15:03:15 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>
# include "libft.h"
# include "types.h"
# include "utils.h"
# include "parsing.h"

void		create_env_list(t_minishell *shell, char **envp);
void		init_env_list(t_env_list *lst);
t_new_envp	*new_env_node(char *name, char *value);
void		list_add_back(t_new_envp **lst, t_new_envp *new);
void		update_shlvl(t_minishell *shell);
char		**env_list_array(t_env_list *env_list);
void		find_env(t_minishell *ms);
char		*create_sub(char *tok);
char		*env_find(char *tok, t_minishell *ms);
char		*process_sub(char *tok, t_minishell *ms);

#endif