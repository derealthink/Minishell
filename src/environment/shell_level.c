/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 19:12:24 by aielo             #+#    #+#             */
/*   Updated: 2025/10/29 18:18:26 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	update_shlvl(t_minishell *shell)
{
	t_new_envp	**current;
	t_new_envp	*target;
	int			shlvl;
	char		*shlvl_c;

	if (!shell || !shell->env_list)
		return ;
	current = &shell->env_list->head;
	while (*current)
	{
		if (ft_strcmp((*current)->name, "SHLVL") == 0)
		{
			target = *current;
			shlvl = ft_atoi(target->value);
			shlvl += 1;
			shlvl_c = ft_itoa(shlvl);
			if (!shlvl_c)
				return ;
			free(target->value);
			target->value = strdup(shlvl_c);
			free(shlvl_c);
			break ;
		}
		current = &(*current)->next;
	}
}
