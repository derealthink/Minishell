#include "environment.h"

void    find_env(t_minishell *ms)
{
    t_token *temp;
    char    *res;

    temp = ms->token_list->head;
    while (temp)
    {
        if (is_env(temp->value) && !temp->s_quotes)
        {
            res = env_str(temp->value, ms);
            if (res)
            {
                free(temp->value);
                temp->value = res;
            }
        }
        temp = temp->next;
    }
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
    while (tok[i] && !is_space(&tok[i]) && !is_quotes(&tok[i]))
    {
        i++;
        len++;
    }
    s = ft_substr(tok, pos, len);
    return (s);
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

char    *process_sub(char *tok, t_minishell *ms)
{
    int     len;
    int     i;
    char    *res;

    len = ft_strlen(tok);
    i = 1;
    if (tok[i] && tok[i] == '?')
        res = ft_itoa(ms->last_exit_status);
    else
        res = env_find(&tok[i], ms);
    return (res);
}


char    *env_str(char *tok, t_minishell *ms)
{
    int         i;
    int         pos;
    size_t      count;
    char        *rest;
    char        *temp;
    char        *exp;
    char        *res;
    char        *joined;

    i = 0;
    pos = 0;
    count = 0;
    res = ft_strdup("");

    while (tok[i])
    {
        // move until next '$' or end
        pos = i;
        while (tok[i] && tok[i] != '$')
            i++;
        count = i - pos;

        // copy the "rest" before '$'
        if (count > 0)
        {
            rest = ft_substr(tok, pos, count);
            joined = ft_strjoin(res, rest);
            free(res);
            free(rest);
            res = joined;
        }

        // handle '$' expansion
        if (tok[i] == '$')
        {
            temp = create_sub(&tok[i]);       // includes '$'
            exp = process_sub(temp, ms);      // expand it
            joined = ft_strjoin(res, exp);    // append expanded value
            free(res);
            free(temp);
            free(exp);
            res = joined;
            i += ft_strlen(temp);             // skip over '$VAR'
        }
    }

    return (res);
}


