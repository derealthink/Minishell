/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:17:00 by aielo             #+#    #+#             */
/*   Updated: 2025/10/06 16:22:42 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	init_env_list(t_env_list *lst);

void	create_env_list(t_minishell *shell, char **envp)
{
	t_new_envp	*node;
	char		**tmp;
	int			i;
	int			j;

	if (!shell)
		return ;
	shell->env_list = (t_env_list *) malloc (sizeof(t_env_list));
	init_env_list(shell->env_list);
	i = 0;
	while (envp[i])
	{
		j = 0;
		tmp = NULL;
		tmp = ft_split(envp[i], '=');
		node = new_env_node(tmp);
		list_add_back(&shell->env_list->head, node);
		while (tmp[j])
			free(tmp[j++]);
		free(tmp);
		i++;
	}
	shell->env_list->len_envp = i;
}

static void	init_env_list(t_env_list *lst)
{
	lst->head = NULL;
	lst->len_envp = 0;
}

t_new_envp	*new_env_node(char **tmp)
{
	t_new_envp	*node;

	if(!tmp)
		return (NULL);
	node = (t_new_envp *) malloc (sizeof(t_new_envp));
	if (!node)
		return (NULL);
	node->name = ft_strdup(tmp[0]);
	if (tmp[1])
		node->value = ft_strdup(tmp[1]);
	else
		node->value = ft_strdup("");
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

char **env_list_array(t_env_list *env_list)
{
	t_new_envp	*tmp;
	char		*temp_env;
	char		**full_env;
	int			i;
	
	if (!env_list || env_list->len_envp == 0)
	{
		full_env = (char **)malloc(sizeof(char *));
		if (full_env)
			full_env[0] = NULL;
		return (full_env);
	}
	tmp = env_list->head;
	i = 0;
	full_env = (char **)malloc(sizeof(char *) * (env_list->len_envp + 1));
	if (!full_env)
		return (NULL);
	while (tmp != NULL)
	{
		temp_env = ft_strjoin(tmp->name, "=");
		if (!temp_env)
			return (NULL);    
		full_env[i] = ft_strjoin(temp_env, tmp->value);
		free(temp_env);
		tmp = tmp->next;
		i++;
	}
	full_env[i] = '\0';
	return (full_env);
}

int	list_size(t_new_envp *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
