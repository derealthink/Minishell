/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:43:17 by uponci            #+#    #+#             */
/*   Updated: 2025/11/03 13:12:19 by aielo            ###   ########.fr       */
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

static int	count_args(t_token *start)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = start;
	while (temp && temp->type != TYPE_PIPE)
	{
		if (!temp->moved && temp->type == TYPE_ARG)
			count++;
		temp = temp->next;
	}
	return (count);
}

void	args_to_cmd(t_cmd *cmd, t_token *start)
{
	int		count;
	t_token	*temp;
	char	**n_args;
	int		i;

	count = count_args(start);
	n_args = malloc(sizeof(char *) * (count + 1));
	if (!n_args)
		return ;
	temp = start;
	i = 0;
	while (temp && temp->type != TYPE_PIPE)
	{
		if (!temp->moved && temp->type == TYPE_ARG)
		{
			n_args[i] = ft_strdup(temp->value);
			temp->moved = 1;
			i++;
		}
		temp = temp->next;
	}
	n_args[i] = NULL;
	cmd->args = n_args;
}
