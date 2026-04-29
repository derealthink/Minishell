/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:17:00 by aielo             #+#    #+#             */
/*   Updated: 2025/10/22 18:30:29 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	init_empty_envp(t_minishell *shell);
static void	add_env_var(t_env_list *env_list, char *name, char *value);
static void	init_new_envp(t_minishell *shell, char **envp);

void	create_env_list(t_minishell *shell, char **envp)
{
	if (!shell)
		return ;
	shell->env_list = (t_env_list *) malloc (sizeof(t_env_list));
	if (!shell->env_list)
		return ;
	init_env_list(shell->env_list);
	if (!envp || !*envp)
		init_empty_envp(shell);
	else
		init_new_envp(shell, envp);
}

void	init_env_list(t_env_list *lst)
{
	lst->head = NULL;
	lst->len_envp = 0;
}

static void	init_empty_envp(t_minishell *shell)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	add_env_var(shell->env_list, "PWD", cwd);
	add_env_var(shell->env_list, "SHLVL", "0");
	add_env_var(shell->env_list, "PATH",
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	add_env_var(shell->env_list, "_", "/usr/bin/env");
}

static void	add_env_var(t_env_list *env_list, char *name, char *value)
{
	t_new_envp	*node;

	node = new_env_node(name, value);
	list_add_back(&env_list->head, node);
	env_list->len_envp++;
}

static void	init_new_envp(t_minishell *shell, char **envp)
{
	t_new_envp	*node;
	char		**tmp;
	int			i;
	int			j;

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
