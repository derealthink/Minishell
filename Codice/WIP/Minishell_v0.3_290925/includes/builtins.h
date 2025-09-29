/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:14 by aielo             #+#    #+#             */
/*   Updated: 2025/09/29 16:56:58 by aielo            ###   ########.fr       */
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

int	is_builtin(char *cmd);
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