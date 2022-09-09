/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:19 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/09 17:14:42 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// static  char    **fill_spltd(char   *var, char   **spltd, int count)
// {
//     int i;
//     int j;
//     int t;
//     i = 0;
//     j = 0;
//     count--;
//     t = count;
//     while(var[i])
//     {
//         spltd[count][j] = var[i];
//         if(var[i] == '$')
//         {
//             spltd[count][j] = '\0';
//             count--;
//             i++;
//             j = 1;
//             spltd[count][0] = '$';
//             while(ft_isalnum(var[i]) || var[i] == '_')
//             {
//                 spltd[count][j] = var[i++];
//                 j++;
//             }
//             spltd[count][j] = '\0';
//             count--;
//             j = 0;
//         }
//         i++;
//         j++;
//     }
//     spltd[count][j] = '\0';
//     while(t >= 0)
//     {
//         printf("%s\n", spltd[t]);
//         t--;
//     }
//     return (spltd);
// }

static  int *char_counter(char  *var, int   count)
{
    int *tab;
    int i;
    int j;
    int t;
    i = -1;
    j = 0;
    tab = malloc(sizeof(int) * count);
    count--;
    t = count;
    while(var[++i])
    {
        if(var[i] == '$')
        {
            if(i != 0)
                tab[count--] = j;
            i++;
            j = 1;
            while(ft_isalnum(var[i]) || var[i] == '_')
            {
                i++;
                j++;
            }
            tab[count--] = j;
            j = 0;
        }
        j++;
    }
    tab[count] = j;

    while(t >= 0)
    {
        printf("len = %d\n", tab[t]);
        t--;
    }
    return(tab);
}

static  int word_counter(char    *var)
{
    int i;
    int count;
    int stat;

    i = -1;
    stat = 1;
    count = 0;
    while(var[++i])
    {
        if (stat == 1 && var[i] != '$')
        {
            stat = 0;
            count++;
        }
        if (var[i] == '$')
        {
            count++;
            i++;
            while (var[i] == '_' || ft_isalnum(var[i]))
                i++;
            if (!var[i])
                break;
            stat = 1;
            i--;
        }
    }
    printf("count = %d\n", count);
    return(count);
}

static void    prep_expnd(char  *var)
{
    char    **spltd;
    int     count;
    int     *tab;

    count   = word_counter(var);
    tab     = char_counter(var, count);
    // spltd = malloc(sizeof(char  *) * (count + 1));
    //spltd[count] = NULL;
    //count--;
    // while(count >= 0)
    // {
    //     //spltd[count] = malloc(sizeof(char) * (tab[count] + 1));
    //     count--;
    // }
    // fill_spltd(var, spltd, word_counter(var));
}

void    static find_var(t_cmd *node, t_env *env)
{
    char    *str;
    t_env   *tmp;

    tmp = env;
    str = ft_strdup(node->str);
    ft_strlcpy(str, node->str + 1, ft_strlen(node->str));
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, str))
        {
            node->str = ft_strdup(tmp->value);
            node->type = WORD;
            return ;
        }
        tmp = tmp->next;
    }
    node->str = ft_strdup("");
    node->type = WORD;
}

void    var_expnd(t_data    *data)
{
    t_cmd   *tmp;

    tmp = data->cmd;
    while(tmp)
    {
        if (tmp->type == SPC)
            tmp = tmp->next;
        if (tmp->type == VARIABLE)
            find_var(tmp, data->env);
        if (tmp->type == EXPND_VB)
            prep_expnd(tmp->str);
        tmp = tmp->next;
    }
}