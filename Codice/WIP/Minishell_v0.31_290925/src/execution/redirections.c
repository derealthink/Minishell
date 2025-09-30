/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:49:22 by aielo             #+#    #+#             */
/*   Updated: 2025/09/30 14:08:16 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executions.h"

int	handle_redirect_in(t_cmd *cmd_list)
{
	int	fd;

	fd = -1; // da rivedere
	if (cmd_list->input_file)
	{
		fd = open(cmd_list->input_file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_list->input_file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
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
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_list->output_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	return (fd);
}

int	here_doc(char *limiter)
{
	static char	*stash;
	int			pipe_fd[2];
	char		*line;
	pid_t		pid;
	
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
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
			break;
			}
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[0]);
}

/*

	< should redirect input.
	> should redirect output (create/truncate).
	>> should redirect output (create/append).
	<< (heredoc) should be given a delimiter, then read the input until a line containing the delimiter is seen. 

	<< (heredoc) should be given a delimiter, then read the input until a line containing the
	delimiter is seen. However, it doesn’t have to update the history!
	get_next_line ha 1 byte still reachable da sistemare?

	Usare unlink("heredoc_tmp"); nel cleanup.
	Just remember to handle the temporary file correctly, perhaps by using O_UNLINK or simply unlinking the file after the command finishes.
*/
