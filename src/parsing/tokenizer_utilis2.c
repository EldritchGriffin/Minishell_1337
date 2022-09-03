/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utilis2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:53:57 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/03 03:24:17 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void   ft_space_skip(char **line, int *i)
{
        while((*line[*i] == ' ' || *line[*i] == '\t' || *line[*i] == '\r'
            || *line[*i] == '\v'))
            (*i)++;
}
