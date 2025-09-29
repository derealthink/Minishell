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

int	is_rin(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '<')
			return (1);
		i++;
	}
	return (0);
}
int	is_rout(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '>')
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

void init_cmd(t_cmd *cmd)
{
    if (!cmd)
        return;
    cmd->path = NULL;
    cmd->args = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->delimiter = NULL;
    cmd->trunc_mode = true;   // standard: default is truncate
    cmd->next = NULL;
}

t_cmd *new_cmd(t_cmd *prev)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    init_cmd(cmd);
    if (prev)
        prev->next = cmd;
    return cmd;
}
