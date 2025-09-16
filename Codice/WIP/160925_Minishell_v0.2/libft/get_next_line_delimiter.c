/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_delimiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aielo <aielo@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:30:56 by aielo             #+#    #+#             */
/*   Updated: 2025/09/15 13:46:34 by aielo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char **stash);
static int	find_next_line(const char *s, int c);
static int	read_and_join(char **stash, int fd);

char	*get_next_line_delimiter(int fd, char **stash)
{
	char		*line;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0 || !stash)
		return (NULL);
	read_size = 1;
	while (read_size > 0)
	{
		line = extract_line(stash);
		if (line)
			return (line);
		read_size = read_and_join(stash, fd);
	}
	if (*stash)
	{
		line = ft_strdup(*stash);
		free (*stash);
		*stash = NULL;
		return (line);
	}
	return (NULL);
}

static char	*extract_line(char **stash)
{
	char	*line;
	char	*remain;
	int		new_index;

	new_index = find_next_line(*stash, '\n');
	if (*stash && (new_index >= 0))
	{
		line = ft_substr(*stash, 0, new_index + 1);
		remain = ft_strdup(*stash + new_index + 1);
		free (*stash);
		*stash = remain;
		return (line);
	}
	return (NULL);
}

static int	find_next_line(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	return (-1);
}

static int	read_and_join(char **stash, int fd)
{
	int		read_size;
	char	buffer[BUFFER_SIZE + 1];
	char	*remain;

	read_size = read(fd, buffer, BUFFER_SIZE);
	if (read_size < 0)
	{
		free(*stash);
		*stash = NULL;
		return (read_size);
	}
	if (read_size == 0)
		return (read_size);
	buffer[read_size] = '\0';
	if (!*stash)
		*stash = ft_strdup(buffer);
	else
	{
		remain = ft_strjoin(*stash, buffer);
		free(*stash);
		*stash = remain;
	}
	return (read_size);
}

/*

char	*get_next_line_delimiter(int fd, char **stash)
{
	char		*line;
	int			read_size;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	read_size = 1;
	while (read_size > 0)
	{
		line = extract_line(&stash[fd]);
		if (line)
			return (line);
		read_size = read_and_join(&stash[fd], fd);
	}
	if (*stash[fd])
	{
		line = ft_strdup(stash[fd]);
		free (stash[fd]);
		stash[fd] = NULL;
		return (line);
	}
	free (stash[fd]);
	stash[fd] = NULL;
	return (NULL);
}

*/