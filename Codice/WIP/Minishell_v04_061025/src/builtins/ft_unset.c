/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/13 17:08:58 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_minishell *shell, char **args)
{
	int			i;

	if (!shell || !args)
		return (shell->last_exit_status = 1);
	shell->last_exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (ft_is_valid_name(args[i]) == 0)
		{
			i++;
			continue ;
		}
		if (delete_env_node(shell, args[i]) == -1)
			return (shell->last_exit_status = -1);
		i++;
	}
	return (shell->last_exit_status);
}

int	delete_env_node(t_minishell *shell, char *name)
{
	t_new_envp	**ptr;
	t_new_envp	*target;

	if (!shell || !name)
		return (-1);
	ptr = &shell->env_list->head;
	while (*ptr)
	{
		if (ft_strcmp((*ptr)->name, name) == 0)
		{
			target = *ptr;
			*ptr = target->next;
			free(target->name);
			free(target->value);
			free(target);
			shell->env_list->len_envp--;
			return (0);
		}
		ptr = &(*ptr)->next;
	}
	return (0);
}
