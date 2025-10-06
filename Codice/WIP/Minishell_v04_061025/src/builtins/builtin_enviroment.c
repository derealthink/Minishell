/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_enviroment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/06 16:19:14 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
			ft_putstr_fd("export: not a valid identifier\n", 2); //corretto messaggio di error?
			args_clear(new_var);
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
			list_add_back(&shell->env_list->head, new);
			shell->env_list->len_envp++;
		}
		args_clear(new_var);
		i++;
	}
	if (shell->last_exit_status != 1)
		shell->last_exit_status = 0;
	return (shell->last_exit_status);
}

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

int ft_unset(char **envp)
{
	(void)envp;
	return (0);
}

int ft_env(t_minishell *shell, char **new_envp)
{
	char	**args = shell->cmd_list->args;
	int		i;
	
	i = 0;
	while(args[i])
			i++;
	if (i > 1)
	{
		ft_putstr_fd("env: ’", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		shell->last_exit_status = 127;
		return (shell->last_exit_status);
	}
	i = 0;
	while (new_envp[i])
	{
		printf("%s\n", new_envp[i]);
		i++;
	}
	return (0);
}

// trova il valore della envp (ex $HOME)
int	env_variable(char **args, char **new_envp)
{
	int		i;
	char	*path_value;
	
	i = 0;
	path_value = NULL;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], args[1], ft_strlen(args[1])) == 0)
		{
			path_value = new_envp[i] + ft_strlen(args[1]);
			break;
		}
		i++;
	}
	if (!path_value)
		return (0);
	printf("%s\n", path_value);
	return (0);
}

// https://docs.vultr.com/how-to-set-environment-variables-in-bash-on-linux