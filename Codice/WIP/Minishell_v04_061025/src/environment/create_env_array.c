/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:17:00 by aielo             #+#    #+#             */
/*   Updated: 2025/10/09 22:11:57 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static char	**env_list_null(char **full_env);
static int	build_array(char **full_env, t_new_envp *tmp, int i);

char	**env_list_array(t_env_list *env_list)
{
	t_new_envp	*tmp;
	char		**full_env;
	int			i;

	full_env = NULL;
	if (!env_list || env_list->len_envp == 0)
		return (full_env = env_list_null(full_env));
	tmp = env_list->head;
	i = 0;
	full_env = (char **)malloc(sizeof(char *) * (env_list->len_envp + 1));
	if (!full_env)
		return (NULL);
	while (tmp != NULL)
	{
		if (build_array(full_env, tmp, i))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	full_env[i] = '\0';
	return (full_env);
}

static char	**env_list_null(char **full_env)
{
	full_env = (char **)malloc(sizeof(char *));
	if (full_env)
		full_env[0] = NULL;
	return (full_env);
}

static int	build_array(char **full_env, t_new_envp *tmp, int i)
{
	char	*temp_env;

	temp_env = ft_strjoin(tmp->name, "=");
	if (!temp_env)
	{
		array_clear(full_env);
		return (1);
	}
	full_env[i] = ft_strjoin(temp_env, tmp->value);
	free(temp_env);
	if (!full_env[i])
	{
		array_clear(full_env);
		return (1);
	}
	return (0);
}
