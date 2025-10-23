/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:14 by aielo             #+#    #+#             */
/*   Updated: 2025/10/22 19:28:07 by aielo            ###   ########.fr       */
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
# include "configuration.h"
# include "types.h"
# include "utils.h"

int	is_parent_builtin(char *cmd);
int	is_child_builtin(char *cmd);
int	execute_builtin(t_minishell *shell, t_cmd *cmd, char ***new_envp);

int	ft_echo(t_minishell *shell, char **args);
int	ft_cd(t_minishell *shell, char **args, char **new_envp);
int	cd_special_cases(char **path, char **args, char **new_envp);
int	ft_pwd(t_minishell *shell, char **new_envp);

int	ft_export(t_minishell *shell, char **args, char **new_envp);
int	print_env_sort(char **new_envp);

int	ft_unset(t_minishell *shell, char **args);
int	ft_env(t_minishell *shell, char **new_envp);

int	ft_exit(t_minishell *shell, char **new_envp);
int	ft_is_numeric(const char *str);
int	ft_atol_limit_check(const char *str, long long *val_out);

int	env_variable(char **args, char **new_envp);
int	ft_is_valid_name(const char *name);
int	update_env_var(t_minishell *shell, char *name, char *value);
int	delete_env_node(t_minishell *shell, char *name);

#endif