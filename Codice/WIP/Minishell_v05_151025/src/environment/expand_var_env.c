#include "environment.h"

void    find_env(t_table *list)
{
    t_token *temp;

    temp = list->head;
    while (temp)
    {
        if (is_env(temp->value) && !temp->s_quotes)
        {
            //function here to expand.
        }
        temp = temp->next;
    }
}

int count_var(char *str)
{
    int i;
    int count;
    int len;

    i = 0;
    count = 0;
    len = ft_strlen(str);
    while (i < len)
    {
        if (str[i] == '$')
        {
            count++;
            if (str[i + 1] == '$')
                i++;
        }
        i++;
    }
    return (count);
}

char    *create_sub(char *tok)
{
    int     i;
    int     pos;
    char    *s;
    size_t     len;

    i = 0;
    while (tok[i] != '$')
        i++;
    pos = i;
    len = 0;
    while (!is_space(&tok[i]) || !is_quotes(&tok[i]))
    {
        i++;
        len++;
    }
    s = ft_substr(tok, pos, len);
    return (s);
}

char    *process_sub(char *tok, t_minishell *ms)
{
    int     len;
    int     i;
    char    *res;

    len = ft_strlen(tok);
    i = 1;
    if (tok[i] && tok[i] == '?')
        res = env_exit(ms);
    else
        res = env_find(&tok[i], ms);
    return (res);
}

char    *env_exit(t_minishell *ms)
{
    char    *res;

    res = ft_itoa(ms->last_exit_status);
    return (res);

}

char    *env_find(char *tok, t_minishell *ms)
{
    t_new_envp  *temp;
    char        *res;

    temp = ms->env_list->head;
    while (temp)
    {
        if (ft_strcmp(temp->name, tok) == 0)
        {    
            res = ft_strdup(temp->value);
            return (res);
        }
        else
            res = ft_strdup("");
        temp = temp->next;
    }
    return (res);
}

char    *env_env(char *tok, t_minishell *ms)
{
    char    **arr;

    
}


