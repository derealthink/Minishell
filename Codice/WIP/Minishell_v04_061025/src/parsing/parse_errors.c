#include "parsing.h"

int unclosed_quotes(char *str)
{
    int i;
    int quotes;

    i = 0;
    quotes = 0;
    while (str[i])
    {
        if ((str[i] == 34 || str[i] == 39) && quotes == '0')
            quotes = str[i];
        else if (str[i] == quotes)
            quotes = 0;
        i++;
    }
    return (quotes);
}

int pipe_misuse(char *str)
{
    int len;
    int i;

    i = 0;
    if (str[i] == '|')
        return (0);
    len = ft_strlen(str);
    if (str[len] == '|')
        return (0);
    while (i < len)
    {
        if (str[i] == '|' && str[i + 1] == '|')
            return (0); 
        i++;
    }
    return (1);
}

