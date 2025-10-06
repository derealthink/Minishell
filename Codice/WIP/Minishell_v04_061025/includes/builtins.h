/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:14 by aielo             #+#    #+#             */
/*   Updated: 2025/10/06 15:41:58 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"
# include "environment.h"
# include "types.h"
# include "utils.h"

int is_parent_builtin(char *cmd);
int is_child_builtin(char *cmd);
int	execute_builtin(t_minishell *shell, t_cmd *cmd, char ***new_envp);

int ft_echo(char **args);
int	ft_cd(char **args, char **envp);
int	ft_pwd(char **envp);

int ft_export(t_minishell *shell, char **args);
int ft_unset(char **envp);
int ft_env(t_minishell *shell, char **envp);

//void	ft_exit(t_cmd *cmd_list, char **envp);
int	ft_exit(t_minishell *shell, char **new_envp);

int	env_variable(char **args, char **envp);
int	ft_is_valid_name(const char *name);
//int	exit_status();

#endif