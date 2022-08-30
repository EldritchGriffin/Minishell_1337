#include "../../headers/minishell.h"


char   get_quote(char line)
{
    if (line == '"')
        return('"');
    return('\'');
}

int redirection_handler(char a , char b, int old_type)
{
    if (a == '>' && b == '>')
            return(APPEND);
    else if(a == '<' && b == '<')
            return (HERDOC);
    else
        return (old_type);
}

void   ft_space_skip(char *line, int *i)
{
        while(line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\r'
            || line[*i] == '\v')
            (*i)++;
}
