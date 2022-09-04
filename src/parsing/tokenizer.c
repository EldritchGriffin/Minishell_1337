/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:14 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/04 04:34:17 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//------------------ tokanization part is not finished , stilll working on it-----------------------------------

int get_token_type(char line)
{
    if (line == '|') 
           return(PIPE);
    else if(line == '\'')
            return(S_QUOTES);
     else if(line == '>')
        return(O_REDIRECTION);
     else if(line == '<')
        return(I_REDIRECTION);
    else if(line == '\"')
            return(D_QUOTES);
    else if(line == '$')
           return(VARIABLE);
    else if(line == ' ' ||line == '\t')
             return(SPC);
    else if(line == '(')
            return(O_BCK);
    else if(line == ')')
            return(C_BCK);
    else
        return (WORD);
}


static bool check_old_type(char *line, int *i, int *words, int *old_type, t_data *data)
{
    if (*old_type == S_QUOTES || *old_type == D_QUOTES)
    {
        if (!quote_handler(line, i, get_quote(line[(*i)]), words))
                return (false);
    }
    else if (*old_type == VARIABLE)
         var_handler(line, i, words, data, old_type);
    return (true);
}

bool ft_break(int a, int b)
{
    if (b == S_QUOTES)
        return (true);
    else if (b == D_QUOTES)
        return (true);
    if (a != b)
        return (true);
    else if (a == b)
        return (false);
    else if(b == SPC)
        return (true);
    return (false);
}

void    get_token(char *line, int *i, int start, t_data  *data)
{   
    int tmp_type;
    int old_type;
    int words;
    int check;

    tmp_type = get_token_type(line[*i]);
    old_type = tmp_type;
    words = -1;
    check = (*i);
    while (1)
    { 
        tmp_type = get_token_type(line[*i]);
        words++;   
        if (ft_break(old_type, tmp_type) || !line[*i])
                break ;
        (*i)++;
    }
    old_type = redirection_handler(line[check], line[check + 1], old_type); 
    if (!check_old_type(line, i, &words, &old_type, data))
        return(data->cmd = NULL, (void)0);
    if (old_type == SPC)
        {
            cmd_list(ft_strdup(" "), old_type, data);
            return ;
        }
    cmd_list(ft_substr(line, start, words), \
            old_type, data);
} 

void    build_token_list(char *line, t_data *data)
{
    int i;

    i = -1;
    while (line[++i])
    {
        get_token(line, &i, i, data);
        i--;
    }
}