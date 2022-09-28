/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execlist_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:51:07 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/28 06:28:31 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char    **prep_excstr(t_cmd *cmd)
{
    char    **str;
    int     i;

    i = 0;
    if(!cmd)
        return (NULL);
    while(cmd)
    {
        if(cmd->type == PIPE)
            break;
        if(cmd->type != SPC)
            i++;
        cmd = cmd->next;
    }
    str = malloc(sizeof(char    *) * (i + 1));
    str[i] = NULL;
    return (str);
}

void   prep_exclist(t_cmd *cmd, t_data    *data)
{
    int count;
    t_exc   *node;

    count = ft_count_pipes(data);
    if(!count)
    {
        add_back_exc(&data->exc, new_node_exc(NULL, data));
        return ;
    }
    while(count)
    {
        add_back_exc(&data->exc, new_node_exc(NULL, data));
        count--;
    }
}

void    build_exclist(t_cmd  *cmd, t_data    *data)
{
    t_exc   *exc;

    prep_exclist(cmd, data);
    exc = data->exc;
    exc->str = prep_excstr(cmd);
    exc->flg = flag_str(cmd);
    exc = exc->next;
    while(cmd)
    {
        if(cmd->type == PIPE)
        {
            exc->str = prep_excstr(cmd->next);
            exc->flg = flag_str(cmd->next);
            exc = exc->next;
        }
        cmd = cmd->next;
    }
}

void    fill_exclist(t_cmd  *cmd, t_data    *data)
{
    t_exc   *tmp;
    int     i;

    i = 0;
    build_exclist(cmd, data);
    tmp = data->exc;
    while(cmd)
    {
        if(cmd->type == PIPE)
        {
            i = 0;
            tmp = tmp->next;
        }
        else
        {
            if(cmd->type != SPC)
                tmp->str[i++] = ft_strdup(cmd->str);
        }
        cmd = cmd->next;
    }
}