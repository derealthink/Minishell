/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/05 17:02:38 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//rinominare builtins_environment.c e builtins_directories.c e un altro nome per environment/environment.c

int ft_export(t_minishell *shell, char **args)
{
	t_new_envp	*current;
	t_new_envp	*new;
	char		**new_var;
	int			i;

	if (!shell || !args)
		return (0);
	current = shell->env_list->head;
	while (args[i])
	{
		new_var = NULL;
		new_var = ft_split(args[i], '=');
		while (current)
		{
			if (ft_strcmp(new_var[0], current->name) == 0 )
			{
				if (new_var[1])
					current->value = strdup(new_var[1]);
				else
					current->value = "";
				free (new_var);
				return (shell->last_exit_status = 0);
			}
			current = current->next;
		}
		new = new_env_node(new_var);
		list_add_back(&shell->env_list->head, new);
		i++;
	}
	return (0);
}

///ask gemini what errors do I get if I use too many args in export? 

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
int	env_variable(char **args, char **envp)
{
	int		i;
	char	*path_value;
	
	i = 0;
	path_value = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], args[1], ft_strlen(args[1])) == 0)
		{
			path_value = envp[i] + ft_strlen(args[1]);
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