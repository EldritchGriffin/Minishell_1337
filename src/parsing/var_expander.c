/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:19 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/21 15:34:24 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char *find_var(char    *var, t_env *env)
{
    char    *str;
    t_env   *tmp;

    tmp = env;
    str = ft_strdup(var);
    ft_strlcpy(str, var + 1, ft_strlen(var));
    while( tmp)
    {
        if (!ft_strcmp(tmp->key, str))
            return (var = ft_strdup(tmp->value), var);
        tmp = tmp->next;
    }
    var = ft_strdup("");
    return (str);
}

char    *join_expnd(char    **spltd, t_env  *env, int count)
{
    char    *str;

    str = ft_strdup("");
    count--;
    while (count >= 0)
    {
        if (spltd[count][0] == '$')
            spltd[count] = find_var(spltd[count], env);
        ft_strcat(str, spltd[count]);
        count--;
    }
    return (str);
}

static  char    **fill_spltd(char   *var, char   **spltd, int count)
{
    int i;
    int j;
    int stat;
    i = -1;
    j = 0;
    stat = 0;
    count--;
    while (var[++i])
    {
        if (var[i] == '$')
        {
            if (i && !stat)
                spltd[count--][j] = '\0';
            spltd[count][0] = '$';
            i++;
            j = 1;
            while (ft_isalnum(var[i]) || var[i] == '_')
            {
                spltd[count][j] = var[i++];
                j++;
            }
            spltd[count--][j] = '\0';
            i--;
            j = - 1;
            stat = 1;
        }
        else
        {
            stat = 0;
            spltd[count][j] = var[i];
        }
        j++;
    }
    if (!var[i] && !stat)
        spltd[count][j] = '\0';
    return (spltd);
}

static  int *char_counter(char  *var, int   count)
{
    int *tab;
    int i;
    int j;
    int stat;
    i = -1;
    j = 0;
    tab = malloc(sizeof(int) * (count + 1));
    stat = 0;
    while (var[++i])
    {
        if (var[i] == '$')
        {
            if (i && !stat)
                tab[count--] = j;
            i++;
            j = 1;
            while (ft_isalnum(var[i]) || var[i] == '_')
            {
                i++;
                j++;
            }
            tab[count--] = j;
            i--;
            j = -1;
            stat = 1;
        }
        else
            stat = 0;
        j++;
    }
    return (tab[count] = j, tab);
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
    return (count);
}

static char    *prep_expnd(char  *var, t_env    *env)
{
    char    **spltd;
    int     count;
    int     *tab;

    count = word_counter(var);
    tab = char_counter(var, count - 1);
    spltd = malloc(sizeof(char  *) * (count + 1));
    spltd[count] = NULL;
    count--;
    while (count >= 0)
    {
        spltd[count] = malloc(sizeof(char) * (tab[count] + 1));
        count--;
    }
    spltd = fill_spltd(var, spltd, word_counter(var));
    return (join_expnd(spltd, env, word_counter(var)));
}


void    var_expnd(t_data    *data)
{
    t_cmd   *tmp;

    tmp = data->cmd;
    while (tmp)
    {
        if (tmp->type == SPC)
            tmp = tmp->next;
        if (tmp->type == VARIABLE)
        {
            tmp->str = find_var(tmp->str, data->env);
            tmp->type = WORD;
        }
        if (tmp->type == EXPND_VB)
        {
            tmp->str = prep_expnd(tmp->str, data->env);
            tmp->type = WORD;
        }
        tmp = tmp->next;
    }
}