/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:35:43 by aielo             #+#    #+#             */
/*   Updated: 2025/09/11 21:42:01 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"

/*
	Your parser would be responsible for creating and populating this linked list. 
	Each t_cmd node represents a single command and holds its arguments, 
	along with file descriptors for any I/O redirections. 
	The input_fd and output_fd would be set to STDIN_FILENO and STDOUT_FILENO by default 
	and updated if redirections are found.

	// Your parser should populate:
	cmd->path = "ls";           // or full path
	cmd->args = {"ls", "-la", NULL};  // including command as args[0]
*/

typedef struct s_cmd
{
	char			*path;
	char			**args;
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
} t_cmd;

void	print_logo(void);

int		here_doc(char *limiter);

char	*find_command_in_path(char *cmd, char **envp);
int		is_builtin(char *cmd);
int		execute_builtin(t_cmd *cmd, char ***envp);

#endif