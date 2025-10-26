/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:49:22 by aielo             #+#    #+#             */
/*   Updated: 2025/10/26 22:28:27 by aielo            ###   ########.fr       */
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
	{
		fd = here_doc(cmd_list->delimiter);
		if (fd == -1 && g_global_signal == SIGINT)
			return (-1);
	}
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
/*
int here_doc(char *limiter)
{
	int pipe_fd[2];
	pid_t pid;
	int status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	
	pid = fork();
	if (pid == 0)
	{
		here_doc_prompt(limiter, pipe_fd);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		
		// Check if heredoc was interrupted by 
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipe_fd[0]);
			g_global_signal = SIGINT;
			return (-1);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipe_fd[0]);
			g_global_signal = SIGINT;
			return (-1);
		}
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (pipe_fd[0]);
}

static void here_doc_prompt(char *limiter, int pipe_fd[2])
{
	char *line;
	size_t limiter_len;

//    setup_heredoc_signals();
	close(pipe_fd[0]);
	limiter_len = ft_strlen(limiter);
	
	while (1)
	{
		line = readline("heredoc> ");
		if (!line) // EOF (Ctrl-D) or signal interrupt
		{ ///restore my setattr?
			if (g_global_signal == SIGINT)
			{
				close(pipe_fd[1]);
				exit(130);
			}
			break;
		}
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\0')
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}
*/

int	here_doc(char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		here_doc_prompt(limiter, pipe_fd);
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (pipe_fd[0]);
}

static void	here_doc_prompt(char *limiter, int pipe_fd[2])
{
	char	*line;
	size_t	limiter_len;

	setup_heredoc_signals();
	close(pipe_fd[0]);
	limiter_len = ft_strlen(limiter);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\0')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

/*
int here_doc(char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		here_doc_prompt(limiter, pipe_fd);
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (pipe_fd[0]);
}

static void here_doc_prompt(char *limiter, int pipe_fd[2])
{
	char	*line;
	size_t	limiter_len;
	
	close(pipe_fd[0]);
	limiter_len = ft_strlen(limiter);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break;
		if (ft_strncmp(line, limiter, limiter_len) == 0 
			&& line[limiter_len] == '\0')
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}
*/
/*
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
*/