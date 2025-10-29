/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uponci <uponci@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:43:17 by uponci            #+#    #+#             */
/*   Updated: 2025/10/29 12:43:18 by uponci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_env(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '$' && (i == 0 || str[i -1] != '\\'))
		{
			if (str[i] && (str[i + 1] == '_' || ft_isalpha(str[i + 1])))
				return (1);
			if (str[i] && ft_strchr("?", str[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

void	init_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	cmd->path = NULL;
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->delimiter = NULL;
	cmd->trunc_mode = 1;
	cmd->next = NULL;
}

t_cmd	*new_cmd(t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	if (prev)
		prev->next = cmd;
	return (cmd);
}
