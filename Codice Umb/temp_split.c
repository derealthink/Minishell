#include "parsing.h"


static int	count_words(char *str, char del)
{
	int	i;
	int	w;
	int	fl;

	i = 0;
	w = 0;
	fl = 0;
	while (str[i])
	{
		if (str[i] != del && fl == 0)
		{
			fl = 1;
			w++;
		}
		if (str[i] == del)
		{
			fl = 0;
		}
		i++;
	}
	return (w);
}

static int	world_len(char *str, int del)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] && str[i] != del)
	{
		i++;
		c++;
	}
	return (c);
	
}

static char	*sub_str(char *str, char del)
{
	int		size;
	int		i;
	char	*res;

	size = world_len(str, del);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = str[i];
		i++;
	}
	res[size] = '\0';
	return (res);
}

char	**ft_split(char *str, char del)
{
	char	**arr;
	char	*word;
	int		i;
	int		j;
	int		count;

	count = count_words(str, del);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == del)
			i++;
		if (str[i] != '\0')
		{
			word = sub_str(&str[i], del);
			if (!word)
				return (NULL);
			arr[j++] = word;
			i = i + world_len(&str[i], del);
		}
	}
	arr[j] = NULL;
	return (arr);	
}