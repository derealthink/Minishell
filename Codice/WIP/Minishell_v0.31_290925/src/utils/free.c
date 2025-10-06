/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:07:37 by aielo             #+#    #+#             */
/*   Updated: 2025/10/04 20:57:52 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "types.h"

//	creare una free_total function con free cmd_list,
//	rl_clear_history e free env_list da aggiungere in in ft_exit()

void	final_cleanup(t_minishell *shell)
{
	if (shell->token_list)
	{
		token_list_clear(shell->token_list);
		shell->token_list = NULL;
	}
	if (shell->cmd_list)
	{
		cmd_list_clear(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell->env_list)
	{
		env_list_clear(shell->env_list);
		free(shell->env_list);
		shell->env_list = NULL;
	}
	rl_clear_history();
}		
	
void	token_list_clear(t_table *token_list)
{
	t_token	*ptr;
	t_token	*next;

	if (!token_list)
		return ;
	ptr = token_list->head;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->value)
			free(ptr->value);
		free(ptr);
		ptr = next;
	}
	free(token_list);
}

void	cmd_list_clear(t_cmd *cmd_list)
{
	t_cmd	*next;
	t_cmd	*ptr;

	if (!cmd_list)
		return ;
	ptr = cmd_list;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->path)
			free(ptr->path);
		if (ptr->args)
			args_clean(ptr->args);
		if (ptr->input_file)
			free(ptr->input_file);
		if (ptr->output_file)
			free(ptr->output_file);
		if (ptr->delimiter)
			free(ptr->delimiter);
		free(ptr);
		ptr = next;
	}
}

void	args_clean(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
	
void	env_list_clear(t_env_list *env_list)
{
	t_new_envp	*ptr;
	t_new_envp	*next;

	if (!env_list)
		return ;
	ptr = env_list->head;
	while (ptr != NULL)
	{
		next = ptr->next;
		if (ptr->name)
			free(ptr->name);
		if (ptr->value)
			free(ptr->value);
		free(ptr);
		ptr = next;
	}
}

void	new_envp_clear(char **new_envp)
{
	int	i;

	if (!new_envp)
		return ;
	i = 0;
	while (new_envp[i])
	{
		free(new_envp[i]);
		i++;
	}
	free(new_envp);
}
