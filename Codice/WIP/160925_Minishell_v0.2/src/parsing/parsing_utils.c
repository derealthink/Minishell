#include "parsing.h"
#include "types.h"

int	is_pipe(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	is_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	is_append(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len - 1)
	{
		if(str[i] == '>' && str[i + 1] == '>')
			return (1);
		i++;
	}
	return (0);
}

int	is_heredoc(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while(i < len - 1)
	{
		if (str[i] == '<' && str[i] == '<')
			return (1);
		i++;
	}
	return (0);
}
