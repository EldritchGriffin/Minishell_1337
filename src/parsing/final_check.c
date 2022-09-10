/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 05:39:17 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/10 17:59:08 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int     operator_handler(char *str, int type)
{
        if (type == PIPE)
        {
            if ((ft_strcmp("|", str) < 0) && ft_strlen(str) != 1)
                    return (0);
        }
        else if (type == I_REDIRECTION)
        {
            if ((ft_strcmp("<", str) < 0) && ft_strlen(str) != 1)
                    return (0);
        }
        else if(type == I_REDIRECTION)
        {
             if ((ft_strcmp(">", str) < 0) && ft_strlen(str) != 1)
                    return (0);
        }
        else if (type == APPEND)
        {
             if ((ft_strcmp(">>", str) < 0) && ft_strlen(str) != 2)
                    return (0);
        }
        else if(type == HERDOC)
        {
         if ((ft_strcmp("<<", str) < 0) && ft_strlen(str) != 2)
                    return (0);
        }
        return (1);
}

int     check_operatrs_first(t_data *data)
{
    t_cmd *tmp;       

    tmp = data->cmd;
    if (tmp->opr && !tmp->next)
        return (unexpected_token(tmp->str[0]), 0);
    return (1);   
}



int     check_operators_sec(t_data *data)
{
    int     i;
    t_cmd   *tmp;

    i = 0;
    tmp = data->cmd;
    while (tmp)
    {   
        if (tmp->opr)
        {
            if ((tmp->next->next->opr && tmp->next->type == SPC) || tmp->next->next->opr)
                    return (unexpected_token(tmp->next->str[0]), 0);
            if (!operator_handler(tmp->str, tmp->type))
                    return (unexpected_token(tmp->str[0]), 0);
        }
        tmp = tmp->next;
    }
    return (1);
}