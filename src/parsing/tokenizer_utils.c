/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:06 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/11 15:02:14 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int     first_check(char *line, char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (line[0] == str[i])
            return (unexpected_token(str[i]), 1);
    }
    return (0);
}


bool    quote_handler(char *line, int *i, char quote, int *words, int *type)
{
    while (line[(*i)])
   { 
        (*i)++;
        (*words)++;
        if (line[*i] == '$' && quote == '"')
        {
            var_handler(line, i, words, type);
            *type = EXPND_VB;
        }
        if (line[*i] ==  quote)
        {
                (*i)++;
                (*words)++;
                return (true);
        }
    }
    return (quotes_error(quote),false);
}

bool env_check(char *str, t_data *data)
{
    t_env *tmp;
    char *rvalue;

    tmp = data->env;
    while(tmp)
    {
        if (!ft_strcmp(str, tmp->key))
                return (true);
        tmp = tmp->next;
    }
    return (false);
}

void    var_handler(char *line, int *i, int *words, int *type)
{
    int *tmp;

    tmp = i;
    while (line[*i] && !((ft_isalnum(line[*i]) || line[*i] == '_')))
    {   
        (*i)++;
        (*words)++;
        if (line[*i] == '$')
            {
                (*i)++;
                (*words)++;
                return ;
            }
    }
    i = tmp;
    while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
    {
        (*i)++;
        (*words)++;
    }
}
