/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 08:18:07 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/12 14:40:59 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int     ft_check_tokens(t_cmd *cmd)
{
    if (cmd->type == PIPE || cmd->type == I_REDIRECTION 
        || cmd->type == O_REDIRECTION)
    {
        if (ft_strlen(cmd->str) != 1)   
                return (0);
    }
    if (cmd->type == APPEND || cmd->type == HERDOC)
    {
        if (ft_strlen(cmd->str) != 2)
            return (0);
    }
    return (1);
}

int  ft_check_toekns2(t_data *data)
{
   t_cmd *cmd;

   cmd = data->cmd;
   while (cmd)
   {
        if (cmd->type == WORD && !cmd->next)
            break ;
        if (cmd->type == PIPE || cmd->type == I_REDIRECTION 
            || cmd->type == O_REDIRECTION)
        {
            if (ft_strlen(cmd->str) != 1)   
                return (unexpected_token(cmd->str[0]), 0);
        }
        if ((cmd->type == I_REDIRECTION || cmd->type == O_REDIRECTION) 
                || (cmd->next->type == SPC && cmd->next->next->type != WORD))
                    return (0);
        if (cmd->type == APPEND || cmd->type == HERDOC)
        {
            if (ft_strlen(cmd->str) != 2)
                return (unexpected_token(cmd->str[0]), 0);
        }
        if (cmd->type == PIPE && cmd->next->type == SPC && cmd->next->next->type != WORD)
                    return (unexpected_token(cmd->str[0]), 0);
    cmd = cmd->next;
   }
   return (1);
}