/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:05:15 by aielo             #+#    #+#             */
/*   Updated: 2025/10/08 13:24:08 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **new_envp)
{
	char	*directory;
	int		i;

	i = 0;
	while (new_envp[i])
	{
		if (ft_strncmp(new_envp[i], "PWD=", 4) == 0)
		{
			directory = new_envp[i] + 4;
			printf("%s\n", directory);
			break ;
		}
		i++;
	}
//	directory = getcwd(NULL, 0);
	if (!directory)
	{
		perror("pwd: ");
		return (1);
	}
//	printf("%s\n", directory);
//	free(directory);
	return (0);
}
// dopo il test uncommentare le lines di ft_pwd, servono da failsafe
// nel caso pwd venga modificata da fuori dalla shell e non con cd
