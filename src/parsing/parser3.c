/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/19 14:06:54 by zrabhi           ###   ########.fr       */
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

int get_redirection(char **cmd, int *in_file, int *out_file, int her_file)
{

    char *str[5] = {">>", "<<", "<", ">", NULL};
    int type[] = {APPEND, I_REDIRECTION, O_REDIRECTION};
    int i;
    int j;
    
    i = -1;
    while(cmd[++i])
    {
        j = -1;
        while (str[++j])
        {
            if (!ft_strcmp(cmd[i], str[j]))
            {
                if (j == 0)
                    *out_file = open(cmd[i + 1], O_RDWR | O_APPEND | O_CREAT ,0777);
                 else if (j == 3)
                     *out_file = open(cmd[i + 1], O_CREAT | O_TRUNC | O_RDWR);
                // else if(j == 2)
                //     *out_file = open(cmd[i + 1], O_CREAT | O_TRUNC | O_RDWR);
                else if (j == 1)
                    *in_file = her_file;
            }
        }      
    }
    return (true);
}



int    rederection_check(t_exc **exc, int her_file)
{
    t_exc *tmp;
    int     i;
    int     j;
    char *str[5] = {">>", "<<", "<", ">", NULL};
    int result;

    result = 0;
    i = -1;
    j = -1;
    tmp = *exc;    
    result = get_redirection(tmp->str, &tmp->in_file, &tmp->out_file, her_file);
    if (result)
    {
     while (tmp->str[++i])
        {
         j = -1;
         while(str[++j])
         {
            if (!ft_strcmp(tmp->str[i], str[j]))
              {
                    tmp->str[i] = 0;
                    tmp->str[i + 1] = 0;
                    break ;
                }
            }
         }
    }
    return (result);
}

void    build_exc_list(char **tab, t_data *data)
{
    int     i;
    int     len;
    int     is_redi;
    char    *str;
    char    **cmd;
    
    len = exctab_len(tab);
    i = -1;
    is_redi = 0;
    while (++i < len)
    {
        str = ft_strdup(tab[i]);
        cmd = ft_split(str, ' ');
        exc_list(cmd, data);      
    }
}