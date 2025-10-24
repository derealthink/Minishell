/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:17:00 by aielo             #+#    #+#             */
/*   Updated: 2025/10/24 14:05:40 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static char		**env_list_null(char **full_env);
static int		build_array(char **full_env, t_new_envp *tmp, int i);
static char		*ft_strjoin_null(char const *s1, char const *s2);
static size_t	ft_length(const char *s);

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
	full_env[i] = NULL;
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
	full_env[i] = ft_strjoin_null(temp_env, tmp->value);
	free(temp_env);
	if (!full_env[i])
	{
		array_clear(full_env);
		return (1);
	}
	return (0);
}

static char	*ft_strjoin_null(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	s3 = (char *) malloc (ft_length(s1) + ft_length(s2) + 1);
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	if (s2)
	{
		while (s2[j] != '\0')
		{
			s3[i + j] = s2[j];
			j++;
		}
	}
	s3[i + j] = '\0';
	return (s3);
}

static size_t	ft_length(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
