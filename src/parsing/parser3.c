/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/21 22:01:21 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
# define  static const char *RDS[5] = {">>", "<<", "<", ">", NULL};

static size_t exctab_len(char **tab)
{
    size_t     i;

    i = 0;
    while (tab[i])
        i++;
    return(i);
}



char *get_redirection(char **cmd, int *in_file, int *out_file, int her_file, int *result)
{
    int     type[] = {APPEND, I_REDIRECTION, O_REDIRECTION};
    int     i;
    int     j;
    int     check;
    char    *str;
    
    check = 0;
    i = -1;
    str = ft_calloc(sizeof(char), exctab_len(cmd));
    if (!str)
        return (NULL);
    while (cmd[++i])
    {
        j = -1;
        check = 0;
        while (RDS[++j])
        {
            if (!ft_strcmp(cmd[i], RDS[j]))
            {
                check = 1;
                i++;
                if (!ft_open(out_file, in_file, j, cmd[i]))
                    *in_file = her_file;
                *result = 1;
            }
        }      
        if (!check)
        {
            ft_strcat(str, cmd[i]);
            ft_strcat(str, ":");
        }
    }
    return (str);
}

int    rederection_check(t_exc **exc, int her_file)
{
    t_exc   *tmp;
    int     i;
    int     result;
    char    *str;

    result = 0;
    i = -1;
    tmp = *exc;    
    str = get_redirection(tmp->str, &tmp->in_file,\
            &tmp->out_file, her_file, &result);
    (*exc)->str = ft_split(str, ':');
    free(str);
    return (result);
}

void    build_exc_list(char **tab, t_data *data)
{
    int     i;
    char    **cmd;

    i = -1;
    int j = -1;
    while (tab[++j])
            tab[j] = ft_strtrim(tab[j], " ");
    while (++i < exctab_len(tab))
    {
        printf("tabb ===== %s\n", tab[i]);
        cmd = ft_split(ft_strdup(tab[i]), ' ');
        exc_list(cmd, data);      
    }
    // free_tab(cmd);
    print_exc(data->exc);
}