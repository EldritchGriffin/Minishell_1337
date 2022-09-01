/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:41:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/01 02:49:22 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


bool check_one(t_cmd *node, t_cmd *node_next)
{

if (((node->type == D_QUOTES || node->type == S_QUOTES || node->type == WORD)) 
    && (node_next->type == D_QUOTES 
        || node_next->type == S_QUOTES || node_next->type == WORD))
            return(true);
return(false);
    
}

int     search_spc_node(t_cmd **cmd)
{
    t_cmd *tmp;
    int i;
    
    i =0;
    tmp = (*cmd);
    while (tmp)
    {
        if (tmp->type == SPC)
                return (i);
        tmp = tmp->next;
        i++;
    } 
    return (0);
}
