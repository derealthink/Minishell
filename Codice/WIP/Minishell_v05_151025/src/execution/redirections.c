/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:49:22 by aielo             #+#    #+#             */
/*   Updated: 2025/10/08 13:20:08 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

static void	here_doc_prompt(char *limiter, int pipe_fd[2]);

int	handle_redirect_in(t_cmd *cmd_list)
{
	int	fd;

	fd = -1;
	if (cmd_list->input_file)
	{
		fd = open(cmd_list->input_file, O_RDONLY);
		if (fd == -1)
			print_simple_error(cmd_list->input_file,
				"No such file or directory");
	}
	else if (cmd_list->delimiter)
		fd = here_doc(cmd_list->delimiter);
	return (fd);
}

int	handle_redirect_out(t_cmd *cmd_list)
{
	int	fd;

	if (cmd_list->trunc_mode == 1)
		fd = open(cmd_list->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd_list->trunc_mode == 0)
		fd = open(cmd_list->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		ft_putstr_fd("Invalid redirection mode\n", 2);
		return (-1);
	}
	if (fd == -1)
		print_simple_error(cmd_list->output_file, "Permission denied");
	return (fd);
}

int	here_doc(char *limiter)
{
	int			pipe_fd[2];
	pid_t		pid;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		here_doc_prompt(limiter, pipe_fd);
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}

static void	here_doc_prompt(char *limiter, int pipe_fd[2])
{
	static char	*stash;
	char		*line;

	close(pipe_fd[0]);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line_delimiter(STDIN_FILENO, &stash);
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& line[ft_strlen(limiter)] == '\n'))
		{
			free(line);
			if (stash)
			{
				free(stash);
				stash = NULL;
			}
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}
