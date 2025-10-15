/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:16:26 by aielo             #+#    #+#             */
/*   Updated: 2025/10/13 17:03:59 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>
# include "libft.h"
# include "types.h"
# include "utils.h"

void		create_env_list(t_minishell *shell, char **envp);
t_new_envp	*new_env_node(char *name, char *value);
void		list_add_back(t_new_envp **lst, t_new_envp *new);

char		**env_list_array(t_env_list *env_list);

#endif