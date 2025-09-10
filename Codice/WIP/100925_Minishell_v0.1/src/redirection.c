/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:49:22 by aielo             #+#    #+#             */
/*   Updated: 2025/09/10 17:06:55 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




// << (heredoc) should be given a delimiter, then read the input until a line containing the
// delimiter is seen. However, it doesn’t have to update the history!
// get_next_line ha 1 byte still reachable da sistemare

int	here_doc(char *limiter)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	fd = open("heredoc_tmp", O_RDONLY);
	return (fd);
}