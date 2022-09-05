/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:28:09 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/05 22:09:03 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int    cmd_str_len(t_data *data)
{
    t_cmd *tmp;
    int i;

    i = 0;
    if(!data->cmd)
        return (0);
    tmp = data->cmd;
    while(tmp)
    {   
        i += ft_strlen(tmp->str);
        tmp = tmp->next;
    }
    return (i);
}

static size_t count_pipes(t_data *data)
{
    size_t  pipe;
    t_cmd   *tmp;

    tmp = data->cmd;
    pipe = 1;
    while (tmp)
    {
        if (tmp->type == PIPE)
            pipe++;
        tmp = tmp->next;
    }
    return (pipe);
}

static size_t count_str(t_data *data)
{
    size_t  count;  
    t_cmd   *tmp;

    tmp = data->cmd;
    count = 0;
    while (tmp)
    {
        if (tmp->type == PIPE || tmp->type == SPC)
                tmp = tmp->next;
        count++;
        tmp = tmp->next;
    }
    return (count);
}

static char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

//  static size_t ft_words(t_data *data)
//  {
//      size_t count;
//      t_cmd *tmp;

//     tmp   = data->cmd;
//     count = 0;
//     while (tmp)
//     {
//         count += ft_strlen(tm->str);
//         if (tmp->type == PIPE)
//             return (count);
//     }
//     return (count);
//  }


char    **parse_args(t_data *data)
{
    int     i;
    int     j;
    int     k;
    int     count = 0;
    char    **tab;
    t_cmd   *tmp;

    tmp = data->cmd;
    k   = 0;
    tab = (char **)malloc(sizeof(char *) * (count_pipes(data) + 1));
    if(!tab)
        return(NULL);
    // while(++k < count_pipes(data))
    // {
    //     tab[k] = (char *)malloc(sizeof(char) * ft_strlen())



    // }
    
    while (tmp && count < count_str(data))
    {
        i = 0;
        j = 0;
        if (tmp->type == PIPE )
            tmp = tmp->next;
        tab[k] = (char *)malloc(sizeof(char) * (ft_strlen(tmp->str) + 1));
        if (!tab[k])
            return(free_tab(tab));
        while (tmp->str && tmp->str[i] && tmp->type != PIPE)
        {
           if (tmp->type == SPC)
                continue;
            tab[k][j++] = tmp->str[i++];
            // if(!tmp->str)
            //     tmp = tmp->next;
            // if (!tmp->str[i + 1])
        }
        tab[k][j] = '\0';
        k++;
        count++;
        tmp = tmp->next;
    }
    tab[k] = 0;
    return (tab);
}