/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/21 20:38:25 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
# define  static const char *RDS[5] = {">>", "<<", "<", ">", NULL};

static int exctab_len(char **tab)
{
    int     i;

    i = -1;
    while (tab[++i]);
        
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
    while(cmd[++i])
    {
        j = -1;
        check = 0;
        while (RDS[++j])
        {
            if (!ft_strcmp(cmd[i], RDS[j]))
            {
                check = 1;
                i++;
                if (j == 0)
                    *out_file = open(cmd[i], O_RDWR | O_APPEND | O_CREAT ,0777);
                else if (j == 3)
                    *out_file = open(cmd[i], O_CREAT | O_TRUNC | O_RDWR, 0644);
                else if(j == 2)
                    *in_file = open(cmd[i], O_RDONLY );
                else if (j == 1)
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

 int ft_check(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (ft_isalpha(str[i]) || str[i] == '-')
                                
                return(1);
    }
    return (0);
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
    int     i, j;
    int     is_redi;
    char    *str;
    char    **cmd;

    j = -1;
    i = 0;
    is_redi = 0;
    while (tab[++j])
		printf("tab ==== %s\n", tab[j]);
    while (i < exctab_len(tab))
    {
        j = -1;
        str = ft_strdup(tab[i]);
        cmd = ft_split(str, ' ');
        printf("cmdd ====== %s\n", cmd[0]);
        exc_list(cmd, data);
        free(str);
        i++;    
    }
    print_exc(data->exc);
}