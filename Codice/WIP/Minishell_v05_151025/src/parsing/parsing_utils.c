#include "parsing.h"
#include "types.h"

int is_pipe(char *str)
{
    return (str && str[0] == '|' && str[1] == '\0');
}

int is_rin(char *str)
{
    return (str && str[0] == '<' && str[1] == '\0');
}

int is_rout(char *str)
{
    return (str && str[0] == '>' && str[1] == '\0');
}

int is_append(char *str)
{
    return (str && str[0] == '>' && str[1] == '>' && str[2] == '\0');
}
int is_heredoc(char *str)
{
    return (str && str[0] == '<' && str[1] == '<' && str[2] == '\0');
}

int is_env(char *str)
{
    return(str && str[0] == '$');
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
    cmd->trunc_mode = 1;   // standard: default is truncate
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
