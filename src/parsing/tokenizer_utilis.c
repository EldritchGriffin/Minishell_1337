/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utilis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:06 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/03 03:18:04 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int     first_check(char *line, char *str)
{
    int i;

    i = -1;
    while(str[++i])
    {
        if (line[0] == str[i])
            return (unexpected_token(str[i]), 1);
    }
    return (0);
}


bool    quote_handler(char *line, int *i, char quote, int *words)
{
   
    while (line[(*i)])
   { 
        (*i)++;
        (*words)++;
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



void    var_handler(char *line, int *i, int *words, t_data *data, int *type)
{
    char    *vbl;
    t_env   *tmp;
    char *check;
    int     j;

    j = 0;
    tmp = data->env;
    vbl = malloc(sizeof(int) * 5);
    if (!vbl)
        return((void)NULL);
    while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
    {
        vbl[j] = line[*i];
        j++;
        (*i)++;
        (*words)++;
    }
    vbl[j] = '\0';
    if (env_check(vbl, data))
            *type = EXPND_VB;
    // free(vbl);
}
