/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:25 by aielo             #+#    #+#             */
/*   Updated: 2025/10/06 15:07:30 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONS_H
# define EXECUTIONS_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "types.h"
# include "builtins.h"
# include "signals.h"
# include "utils.h"

int		execute_cmd(char *cmd_path, char **args, char **envp);
char	*find_executable(char *cmd, char **path_dirs);

char	*find_command_in_path(char *cmd, char **envp);

//int		execute_pipeline(t_cmd *cmd_list, char **envp);
int		execute_pipeline(t_minishell *shell, char **new_envp) ;
int		create_pipes(int num_cmds, int *pipes);
void	setup_in_out(t_cmd *cmd, int *pipes, int i, int num_cmds);
void	close_all_pipes(int *pipes, int num_fds);
//void	parent_wait(int num_cmds);
void	parent_wait(t_minishell *shell, int num_cmds);

int		handle_redirect_in(t_cmd *cmd_list);
int		handle_redirect_out(t_cmd *cmd_list);
int		here_doc(char *limiter);

#endif