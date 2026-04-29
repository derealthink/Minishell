/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:17:00 by aielo             #+#    #+#             */
/*   Updated: 2025/10/22 11:36:13 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_new_envp	*new_env_node(char *name, char *value)
{
	t_new_envp	*node;

	if (!name)
		return (NULL);
	node = (t_new_envp *) malloc (sizeof(t_new_envp));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = ft_strdup("");
	if (!node->value)
	{
		free(node->name);
		free(node);
	}
	node->next = NULL;
	return (node);
}

void	list_add_back(t_new_envp **lst, t_new_envp *new)
{
	t_new_envp	*ptr;

	if (!new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}
