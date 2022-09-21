/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 03:49:29 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/21 21:59:56 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


t_exc *new_node_exc(char **str, t_data *data)
{
    t_exc *new_node;

    new_node = ft_malloc(sizeof(t_exc), &data->ptrs);
    new_node->str = str;
    new_node->in_file = 0;
    new_node->out_file = 1;
    new_node->next = NULL;
    return(new_node);
}

static void  add_back_exc(t_exc **exc, t_exc *new_node)
{
    t_exc *tmp;
    
    if (!exc || !new_node)
        return ;
    if (!*exc)
        return(*exc = new_node, (void)0);
    tmp = *exc;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    return ;
}

void    exc_list(char **str, t_data *data)
{
    add_back_exc(&data->exc, new_node_exc(str, data));
}