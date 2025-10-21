/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:17:00 by aielo             #+#    #+#             */
/*   Updated: 2025/10/16 18:26:16 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	create_env_list(t_minishell *shell, char **envp)
{
	t_new_envp	*node;
	char		**tmp;
	int			i;
	int			j;

	if (!shell)
		return ;
	shell->env_list = (t_env_list *) malloc (sizeof(t_env_list));
	if (!shell->env_list)
		return ;
	init_env_list(shell->env_list);
	i = 0;
	while (envp[i])
	{
		j = 0;
		tmp = NULL;
		tmp = ft_split(envp[i], '=');
		node = new_env_node(tmp[0], tmp[1]);
		list_add_back(&shell->env_list->head, node);
		while (tmp[j])
			free(tmp[j++]);
		free(tmp);
		i++;
	}
	shell->env_list->len_envp = i;
}

void	init_env_list(t_env_list *lst)
{
	lst->head = NULL;
	lst->len_envp = 0;
}

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
