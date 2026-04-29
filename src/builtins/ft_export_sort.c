/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/16 18:43:30 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	create_new_list(t_env_list **sort_env, char **envp);
static void	sort_env_list(t_new_envp *head_ref);
static void	swap_data(t_new_envp *a, t_new_envp *b);

int	print_env_sort(char **new_envp)
{
	t_env_list	*sort_env;
	t_new_envp	*current;

	create_new_list(&sort_env, new_envp);
	sort_env_list(sort_env->head);
	current = sort_env->head;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		if (current->value && current->value[0] != '\0')
			ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
	env_list_clear(sort_env);
	return (0);
}

static void	create_new_list(t_env_list **sort_env, char **envp)
{
	t_new_envp	*node;
	char		**tmp;
	int			i;
	int			j;

	if (!envp)
		return ;
	*sort_env = (t_env_list *) malloc (sizeof(t_env_list));
	if (!(*sort_env))
		return ;
	init_env_list(*sort_env);
	i = 0;
	while (envp[i])
	{
		j = 0;
		tmp = NULL;
		tmp = ft_split(envp[i], '=');
		node = new_env_node(tmp[0], tmp[1]);
		list_add_back(&(*sort_env)->head, node);
		while (tmp[j])
			free(tmp[j++]);
		free(tmp);
		i++;
	}
	(*sort_env)->len_envp = i;
}

static void	sort_env_list(t_new_envp *head_ref)
{
	t_new_envp	*end;
	t_new_envp	*current;
	int			swapped;

	if (head_ref == NULL || head_ref->next == NULL)
		return ;
	end = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head_ref;
		while (current->next != end)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				swap_data(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		end = current;
	}
}

static void	swap_data(t_new_envp *a, t_new_envp *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	a->name = b->name;
	b->name = temp_name;
	temp_value = a->value;
	a->value = b->value;
	b->value = temp_value;
}
