/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/14 16:50:07 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	handle_assignment_export(t_minishell *shell, char *arg, char *equals_sign);
static int	handle_simple_export(t_minishell *shell, char *arg);
static int	print_env_sort(t_minishell *shell);
//static int	ft_print_export_list(t_minishell *shell);
//static void	sort_env_list(t_minishell *shell);
//static void swap_data(t_new_envp *a, t_new_envp *b);

int	ft_export(t_minishell *shell, char **args)
{
	int i;
	char *equals_sign;

	if (!shell)
		return (1);
	shell->last_exit_status = 0;
	if (!args[1])
		return (print_env_sort(shell)); 
	i = 1;
	while (args[i])
	{
		equals_sign = ft_strchr(args[i], '=');
		if (equals_sign)
		{
			if (handle_assignment_export(shell, args[i], equals_sign) != 0)
				return (shell->last_exit_status);
		}
		else
		{
			if (handle_simple_export(shell, args[i]) != 0)
				return (shell->last_exit_status);
		}
		i++;
	}
	return (shell->last_exit_status);
}

static int	handle_assignment_export(t_minishell *shell, char *arg, char *equals_sign)
{
	size_t  name_len;
	char    *name;
	char    *value;
	int     ret;

	name_len = equals_sign - arg;
	name = ft_strndup(arg, name_len); 
	if (!name)
		return (-1);
	value = equals_sign + 1;
	if (ft_is_valid_name(name) == 0)
	{
		print_quoted_error("export", name, "not a valid identifier");
		free(name); 
		shell->last_exit_status = 1;
		return (1);
	}
	ret = update_env_var(shell, name, value); 
	free(name);
	return (ret);
}

static int handle_simple_export(t_minishell *shell, char *arg)
{
	if (ft_is_valid_name(arg) == 0)
	{
		print_quoted_error("export", arg, "not a valid identifier");
		shell->last_exit_status = 1;
		return (1);
	}
	return (update_env_var(shell, arg, NULL)); 
}

static int	print_env_sort(t_minishell *shell)
{
	char	**sort_envp;

	sort_envp = env_list_array(shell->env_list);
//	printf("SORT_ENVP!\n\n");
//	ft_env(shell, sort_envp);
// va fatto con una copia della linked list perche¨ serve name e value
	array_clear(sort_envp);
	return (shell->last_exit_status = 0);
}

/*
static int ft_print_export_list(t_minishell *shell)
{
	t_new_envp *current;
	
	sort_env_list(shell); fare copia di linked list?
	current = shell->env_list->head;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		if (current->value && current->value[0] != '\0')
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}		
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
	return (0);
}

static void	sort_env_list(t_minishell *shell)
{
	t_new_envp	*head_ref;
	t_new_envp	*end;
	t_new_envp	*current;
	int			swapped;

	head_ref = shell->env_list->head;
	end = NULL;
	if(head_ref || head_ref->next == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head_ref;
		while (current != NULL && current->next != end)
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

static void swap_data(t_new_envp *a, t_new_envp *b)
{
	char *temp_name;
	char *temp_value;

	temp_name = a->name;
	a->name = b->name;
	b->name = temp_name;
	temp_value = a->value;
	a->value = b->value;
	b->value = temp_value;
}
*/