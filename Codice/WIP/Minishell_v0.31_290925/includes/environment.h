/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:16:26 by aielo             #+#    #+#             */
/*   Updated: 2025/10/05 16:39:26 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdlib.h>
# include "libft.h"
# include "types.h"

void	create_env_list(t_minishell *shell, char **envp);
char 	**env_list_array(t_env_list *env_list);

t_new_envp	*new_env_node(char **tmp);
void	list_add_back(t_new_envp **lst, t_new_envp *new);
int	list_size(t_new_envp *lst);

#endif