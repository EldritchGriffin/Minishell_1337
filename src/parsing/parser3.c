/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/09 16:56:36 by zrabhi           ###   ########.fr       */
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
//  static char get_delemiter(char *str)
// {
//      int i;
//      i = -1;
//      while(str[++i])
//     {
//         if (str[i] == '>' || str[i] == '<')
                
        
//     }


    
//  }

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
        // while(cmd[++j])
        //     printf("cmd ====== %s\n", cmd[j]);
        exc_list(cmd, data);
    }
    free(str);
    // free_tab(cmd);
}