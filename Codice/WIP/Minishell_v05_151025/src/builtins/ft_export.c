/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/10/16 18:46:08 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	handle_assignment_export(t_minishell *shell, char *arg,
				char *equals_sign);
static int	handle_simple_export(t_minishell *shell, char *arg);

int	ft_export(t_minishell *shell, char **args, char **new_envp)
{
	int		i;
	char	*equals_sign;

	if (!shell)
		return (1);
	shell->last_exit_status = 0;
	if (!args[1])
		return (print_env_sort(new_envp));
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

static int	handle_assignment_export(t_minishell *shell, char *arg,
				char *equals_sign)
{
	size_t	name_len;
	char	*name;
	char	*value;
	int		ret;

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

static int	handle_simple_export(t_minishell *shell, char *arg)
{
	if (ft_is_valid_name(arg) == 0)
	{
		print_quoted_error("export", arg, "not a valid identifier");
		shell->last_exit_status = 1;
		return (1);
	}
	return (update_env_var(shell, arg, NULL));
}
