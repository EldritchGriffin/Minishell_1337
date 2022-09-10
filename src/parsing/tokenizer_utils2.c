/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:53:57 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/10 18:01:24 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


char   get_quote(char line)
{
    if (line == '"')
        return('"');
    return('\'');
}

int redirection_handler(char a , char b, int old_type, bool *operator)
{
    if (a == '>' && b == '>')
            return((*operator = true), APPEND);
    else if (a == '<' && b == '<')
            return ((*operator = true), HERDOC);
    else
        return (old_type);
}

void   ft_space_skip(char **line, int *i)
{
    while ((*line[*i] == ' ' || *line[*i] == '\t' || *line[*i] == '\r'
        || *line[*i] == '\v'))
        (*i)++;
}
