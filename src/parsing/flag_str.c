/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 04:11:54 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/28 04:17:28 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int count_char(t_cmd *cmd)
{
    int i;

    i = 0;
    while(cmd)
    {
        if(cmd->type == PIPE)
            break;
        if(cmd->type != SPC)
            i++;
        cmd = cmd->next;
    }
    return (i);
}

char    *flag_str(t_cmd *cmd)
{
    int i;
    char    *str;

    i = count_char(cmd);
    str = malloc(sizeof(char) * i + 1);
    str[i] = '\0';
    i = 0;
    while(cmd)
    {
        if(cmd->type != SPC)
        {    
            if(cmd->type == PIPE)
                break;
            if(cmd->type == WORD)
                str[i] = '1';
            else
                str[i] = '0';
            i++;
        }
        cmd = cmd->next;
    }
    return (str);
}