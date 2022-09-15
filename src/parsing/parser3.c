/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/15 11:42:36 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static size_t exctab_len(char **tab)
{
    size_t     i;

    i = 0;
    while (tab[i])
        i++;
    return(i);
}



// static void get_redirection(char **cmd, int *redi)
// {

//     char *str[4] = {">>", "<<", "<", ">", NULL};
//     int type[] = {APPEND, HERDOC, I_REDIRECTION, O_REDIRECTION};
//     int i;
//     int j;
    
//     j = 0;
//     i = 0;
//     while(cmd[i])
//     {
//          j = -1;
//          whiel(str[++j])
//          {
//              if (!ft_strcmp(cmd[i], str[j]))
//                     *redi = type[j];
//          }      
//     }
// }


void    build_exc_list(char **tab, t_data *data)
{
    int     i;
    int     len;
    char    *str;
    char    **cmd;
    
    len = exctab_len(tab);
    i = -1;
    int j;
    while (++i < len)
    {
        j = -1;
        str = ft_strdup(tab[i]);
        cmd = ft_split(str, ' ');
       
        exc_list(cmd, data);
    }
    free(str);
}