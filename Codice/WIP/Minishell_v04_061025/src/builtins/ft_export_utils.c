/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/14 13:48:04 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int update_existing_node(t_new_envp *node, char *value);

int	ft_is_valid_name(const char *name)
{
	int	i;

	if (!name || *name == '\0' || *name == '=')
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	update_env_var(t_minishell *shell, char *name, char *value)
{
	t_new_envp	*current;
	t_new_envp	*new_node;

	if (!shell || !name)
		return (-1);
	current = shell->env_list->head;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
			return (update_existing_node(current, value));
		current = current->next;
	}
	if (value != NULL)
	{
		new_node = new_env_node(name, value);
		if (!new_node)
			return (-1);
		list_add_back(&shell->env_list->head, new_node);
		shell->env_list->len_envp++;
		return (0);
	}
	return (0);
}

static int update_existing_node(t_new_envp *node, char *value)
{
	free(node->value);
	if (value)
		node->value = strdup(value);
	else
		node->value = strdup("");
	if (!node->value)
		return (-1);
	return (0);
}

// https://docs.vultr.com/how-to-set-environment-variables-in-bash-on-linux

/*
int ft_export(t_minishell *shell, char **args)
{
	t_new_envp	*current;
	t_new_envp	*new;
	char		**new_var;
	int			found;
	int			i;

	if (!shell || !args)
		return (shell->last_exit_status = 1);
	i = 1;
	while (args[i])
	{
		new_var = ft_split(args[i], '=');
		if (ft_is_valid_name(new_var[0]) ==  0)
		{
			print_quoted_error("export", new_var[0], "not a valid identifier");
			array_clear(new_var);
			shell->last_exit_status = 1;
			i++;
			continue ;
		}
		current = shell->env_list->head;
		found = 0;
		while (current)
		{
			if (ft_strcmp(new_var[0], current->name) == 0 )
			{
				free(current->value);
				if (new_var[1])
					current->value = strdup(new_var[1]);
				else
					current->value = strdup("");
				found = 1;
				break ;
			}
			current = current->next;
		}
		if (found == 0 && new_var[1] != NULL)
		{
			new = new_env_node(new_var);
			if (!new)
				return (shell->last_exit_status = -1);
			list_add_back(&shell->env_list->head, new);
			shell->env_list->len_envp++;
		}
		array_clear(new_var);
		i++;
	}
	if (shell->last_exit_status != 1)
		shell->last_exit_status = 0;
	return (shell->last_exit_status);
}
*/