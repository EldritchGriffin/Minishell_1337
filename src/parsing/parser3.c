/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/18 20:23:30 by zrabhi           ###   ########.fr       */
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



static int get_redirection(char **cmd, int *in_file, int *out_file, int her_file)
{

    char *str[5] = {">>", "<<", "<", ">", NULL};
    int type[] = {APPEND, HERDOC, I_REDIRECTION, O_REDIRECTION};
    char *ptr = NULL;
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
                if (j < 3 && j != 1)
                    *out_file = open(cmd[i + 1], O_RDWR | O_APPEND | O_CREAT ,0777);
                // else if (j == 3)
                //     *out_file = open(cmd[i + 1], O_CREAT | O_TRUNC | O_RDWR);
                // else if(j == 2)
                //     *out_file = open(cmd[i + 1], O_CREAT | O_TRUNC | O_RDWR);
                else if (j == 1)
                    *in_file = her_file;
                cmd[i] = ft_strdup(" ");
                cmd[i + 1] = ft_strdup(" ");
                return(true);
            }
        }      
    }
    return (false);
}



static int    rederection_check(t_data **data, int her_file)
{
    t_exc *tmp;
    int result = 0;

    tmp = (*data)->exc;
    while (tmp != NULL)
    {
        result = get_redirection(tmp->str, &tmp->in_file, &tmp->out_file, her_file);
        tmp = tmp->next;
    }  
    return (result);
}

static void remove_redi(t_exc **exc)
{



    
} 

int    build_exc_list(char **tab, t_data *data, int her_file)
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
        is_redi = rederection_check(&data, her_file);        
    }
    free(str);
    return(is_redi);
}