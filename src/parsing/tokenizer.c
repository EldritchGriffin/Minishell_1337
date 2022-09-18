/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:14 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/17 13:33:19 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//------------------ tokanization part is not finished , stilll working on it-----------------------------------

int get_token_type(char line, bool *operator)
{
    if (line == '|') 
           return((*operator = true),PIPE);
    else if (line == '\'')
            return(S_QUOTES);
     else if (line == '>')
        return ((*operator = true), O_REDIRECTION);
     else if (line == '<')
        return ((*operator = true), I_REDIRECTION);
    else if (line == '\"')
            return (D_QUOTES);
    else if (line == '$')
           return (VARIABLE);
    else if (line == ' ' || line == '\t')
             return(SPC);
    else
        return (WORD);
}


static bool check_old_type(char *line, int *i, int *words, int *old_type)
{
    if (*old_type == S_QUOTES || *old_type == D_QUOTES)
    {
        if (!quote_handler(line, i, get_quote(line[(*i)]), words, old_type))
                return (false);
    }
    else if (*old_type == VARIABLE)
         var_handler(line, i, words, old_type);
    return (true);
}

bool ft_break(int a, int b)
{
    if (b == VARIABLE)
        return(true);
    else if (b == S_QUOTES)
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
    bool operator;

    operator = false;
    tmp_type = get_token_type(line[*i], &operator);
    old_type = tmp_type;
    words = -1;
    check = (*i);
    while (1)
    { 
        tmp_type = get_token_type(line[*i], &operator);
        words++;   
        if (ft_break(old_type, tmp_type) || !line[*i])
                break ;
        (*i)++;
    }
    old_type = redirection_handler(line[check], line[check + 1], old_type, &operator); 
    if (!check_old_type(line, i, &words, &old_type))
        return(data->cmd = NULL, (void)0);
    if (old_type == SPC)
           return (cmd_list(ft_strdup(" "), old_type, 0, data), (void)0);
    cmd_list(ft_substr(line, start, words), \
            old_type, operator, data);
} 

int    build_token_list(char *line, t_data *data, int *her_file)
{
    int     i;
    t_cmd   *tmp;
    t_cmd   *hdc;
    
    i = -1;
    while (line[++i])
    {
        get_token(line, &i, i, data);
        i--;
    }
    tmp = data->cmd;
    if (!tmp)
        return (0);
    while (tmp)
    {
        if (tmp->type == S_QUOTES || tmp->type == D_QUOTES || tmp->type == EXPND_VB)
            tmp->str = rmv_quotes(tmp->str);
        tmp = tmp->next;
    }
    if (!check_operatrs_first(data))
            return (0);
    hdc = data->cmd;
    while (hdc)
    {
        if (hdc->type == HERDOC)
            {
                printf("im hre");
                if (!hdc->next->opr && hdc->next->type != SPC)
                  *her_file = here_doc(hdc->next, data);
                else if (!hdc->next->next->opr)
                  *her_file =  here_doc(hdc->next->next, data);
                printf("her_file %d\n", *her_file);
            }
        hdc = hdc->next;
    }
    if (!check_operators_sec(data))
             return (0);
    return (1);
}