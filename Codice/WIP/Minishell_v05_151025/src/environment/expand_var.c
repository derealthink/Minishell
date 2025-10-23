#include "environment.h"

#include "environment.h"

/* Extracts substring starting from '$' and including the variable name */
char    *create_sub(char *tok)
{
    int     i;
    int     pos;
    size_t  len;
    char    *s;

    i = 0;
    while (tok[i] && tok[i] != '$')
        i++;
    pos = i;
    len = 1;                     // include '$'
    i++;
    while (tok[i] && !is_space(tok[i]) && !is_quotes(tok[i]) && tok[i] != '$')
    {
        i++;
        len++;
    }
    s = ft_substr(tok, pos, len);
    return (s);
}

/* Finds variable name 'tok' (without '$') in the environment list */
char    *env_find(char *tok, t_minishell *ms)
{
    t_new_envp  *temp;

    temp = ms->env_list->head;
    while (temp)
    {
        if (ft_strcmp(temp->name, tok) == 0)
            return (ft_strdup(temp->value));
        temp = temp->next;
    }
    return (ft_strdup(""));
}

/* Expands a single variable token like "$VAR" or "$?" */
char    *process_sub(char *tok, t_minishell *ms)
{
    char    *res;

    if (!tok || tok[0] != '$')
        return (ft_strdup(tok));
    if (tok[1] == '\0')                     // '$' alone
        return (ft_strdup(""));
    if (tok[1] == '?')                      // special case
        res = ft_itoa(ms->last_exit_status);
    else
        res = env_find(&tok[1], ms);        // skip '$'
    return (res);
}

/* Expands all variables in the given token string */
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
        pos = i;
        while (tok[i] && tok[i] != '$')
            i++;
        count = i - pos;

        // Copy literal text before '$'
        if (count > 0)
        {
            rest = ft_substr(tok, pos, count);
            joined = ft_strjoin(res, rest);
            free(res);
            free(rest);
            res = joined;
        }

        // Handle '$' expansion
        if (tok[i] == '$')
        {
            temp = create_sub(&tok[i]);   // includes '$'
            if (!temp)
                break;
            exp = process_sub(temp, ms);  // expand it
            joined = ft_strjoin(res, exp);
            free(res);
            free(exp);
            res = joined;
            i += ft_strlen(temp);         // skip over '$VAR'
            free(temp);
        }
    }
    return (res);
}

/* Goes through each token in the list and expands environment variables */
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


