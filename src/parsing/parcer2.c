/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:28:09 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/04 04:41:13 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int    cmd_str_len(t_data *data)
{
    t_cmd *tmp;
    int i;

    i = 0;
    if(!data->cmd)
        return (0);
    tmp = data->cmd;
    while(tmp)
    {   
        i += ft_strlen(tmp->str);
        tmp = tmp->next;
    }
    return (i);
}

char    **parse_args(t_data *data)
{
    int i;
    int j;
    char **tab;
    char *str;
    int pipe;
    t_cmd *tmp;

    // if (!data->cmd)
    //     return (NULL);
    pipe = 0; // to count how many pipes
    j = 0;
    tmp = data->cmd;
    str = malloc(sizeof(char) * (cmd_str_len(data) + 1));
    if (!str)
        return (NULL);
    while (tmp)
    {
        i = 0;
        if (tmp->type == PIPE)
            pipe++;
        while (tmp->str &&tmp->str[i])
            str[j++] = tmp->str[i++];
        tmp = tmp->next;
    }
    str[j] = '\0';
    printf("pipes ===== %d\n", pipe);
    tab = ft_split(str, '|');
    if (!tab)
        return (NULL);
    return (tab);
}