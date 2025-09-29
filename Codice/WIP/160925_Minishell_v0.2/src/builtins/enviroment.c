/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:32:42 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 15:01:38 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_export(char **envp)
{
	(void)envp;
	return (0);
}

int ft_unset(char **envp)
{
	(void)envp;
	return (0);
}

int ft_env(char **envp)
{
	int		i;
	
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

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
		return (NULL);
	printf("%s\n", path_value);
	return (0);
}

int	exit_status()
{
	printf("%d\n", WEXITSTATUS(status));
	return (0);
}