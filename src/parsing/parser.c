/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:53:30 by zrabhi            #+#    #+#             */
/*   Updated: 2022/08/31 17:54:03 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


void    join_unspaced(t_cmd   **node, t_cmd    **node_next, t_data  *data)
{
    char    *str;
    char    *join;
    t_cmd   *new_node;
    if(!*node || !*node_next || (*node_next)->type == SPC)
        return ;
    str = (*node)->str;
    if ((*node)->type == D_QUOTES || (*node)->type == S_QUOTES)
        str = rmv_quotes((*node)->str);
    join = (*node_next)->str;
    if ((*node_next)->type == D_QUOTES || (*node_next)->type == S_QUOTES)
        join = rmv_quotes(join);
    str = ft_strjoin(str, join);
    new_node = new_node_cmd(str, WORD, data);
    if(!(*node)->prev && !(*node_next)->next)
        return (data->cmd = new_node, (void)0);
    else if(!(*node)->prev && (*node_next)->next)
    {
        (*node_next)->next->prev = new_node;
        new_node->next = (*node_next)->next;
        (*node) = new_node;
        printf("%s   |   %s    | %s\n", (*node)->str, (*node_next)->str, new_node->str);
        return ;
    }
    else if (!(*node_next)->next && (*node)->prev)
        return ((*node)->prev->next = new_node, (void)0);
    else if((*node_next)->next && (*node)->prev)
    {
        (*node)->prev->next = new_node;
        (*node_next)->next->prev = new_node;
         new_node->next = (*node_next)->next;
        (*node_next) = new_node;
        // return ;
    }
}

