/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/16 17:07:24 by zrabhi           ###   ########.fr       */
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



static void get_redirection(char **cmd, int *int_file, int *out_file)
{

    char *str[4] = {">>", "<<", "<", ">", NULL};
    int type[] = {APPEND, HERDOC, I_REDIRECTION, O_REDIRECTION};
    char *ptr = NULL;
    int i;
    int j;
    
    j = 0;
    i = 0;
    while(cmd[i])
    {
        j = -1;
        while (str[++j])
        {
            if (!ft_strcmp(cmd[i], str[j]))
            {
                if (j == 0)
                    *out_file = open(cmd[i + 1], O_CREAT | O_APPEND | O_RDWR);
                else if (j == 3)
                    *out_file = open(cmd[i + 1], O_CREAT | O_TRUNC | O_RDWR);
                else if(j == 2)
                    *out_file = open(cmd[i + 1], O_CREAT | O_TRUNC | O_RDWR);
                else if(j == 1)
                    *out_file == here_doc()
                // *redi = type[j];
            }
        }      
    }
}



// void    rederection_check(t_data **data)
// {
//     t_exc *tmp;

//     tmp = (*data)->exc;
//     while(tmp != NULL){
        
//         get_redirection(tmp->str, &tmp->in_file, &tmp->out_file);
//         tmp = tmp->next;
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