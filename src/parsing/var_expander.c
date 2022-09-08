/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:19 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/08 15:56:48 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static  int *char_counter(char  *var, int   count)
{
    int *tab;
    int i;
    int j;

    i = -1;
    j = 0;
    tab = malloc(sizeof(int) * count);
    count--;
    while(var[++i])
    {
        if(var[i] == '$')
        {
            tab[count--] = j;
            i++;
            j = 1;
            while(ft_isalnum(var[i]) || var[i++] == '_')
            {
                i++;
                j++;
            } 
            tab[count--] = j;
            j = 0;
        }
        j++;
    }
    return(tab);
}

static  int word_counter(char    *var)
{
    int i;
    int count;

    i = 0;
    count = 1;
    while(var[i])
    {
        if (var[i] == '$')
        {
            count++;
            i++;
            while(ft_isalnum(var[i]) || var[i] == '_')
                i++;
            if(!var[i])
                return(count);
            count++;
        }
        i++;
    }
    return(count);
}

static void    prep_expnd(char  *var)
{
    char    **spltd;
    int     count;
    int     *tab;

    count   = word_counter(var);
    tab     = char_counter(var, count);
    spltd = malloc(sizeof(char  *) * (count + 1));
    spltd[count--] = NULL;
    while(count >= 0)
    {
        spltd[count] = malloc(sizeof(char) * (tab[count] + 1));
        count--;
    }
    //FIXME almost done with the expansion part;
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
        if(tmp->type == SPC)
            tmp = tmp->next;
        if(tmp->type == VARIABLE || tmp->type == EXPND_VB)
            find_var(tmp, data->env);
        if(tmp->type == D_QUOTES)
            prep_expnd(tmp->str);
        tmp = tmp->next;
    }
}