/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:14 by aielo             #+#    #+#             */
/*   Updated: 2025/09/30 14:00:56 by aielo            ###   ########.fr       */
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
# include "types.h"

int is_parent_builtin(char *cmd);
int is_child_builtin(char *cmd);
int	execute_builtin(t_cmd *cmd, char ***envp);

int ft_echo(char **args);
int	ft_cd(char **args);
int	ft_pwd(void);

int ft_export(char **envp);
int ft_unset(char **envp);
int ft_env(char **envp);

int	env_variable(char **args, char **envp);
//int	exit_status();

#endif