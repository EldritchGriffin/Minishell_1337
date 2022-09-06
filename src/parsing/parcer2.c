/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:28:09 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/06 05:56:18 by zrabhi           ###   ########.fr       */
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

 static size_t ft_words(t_cmd *data)
 {
    size_t count;
    t_cmd *tmp;
    
    count = 0;
    tmp = data;
    while (tmp)
    {
        count += ft_strlen(tmp->str);
        if (tmp->type == PIPE)
            return (count);
        tmp = tmp->next;
    }
    return (count);
 }




char **parse_args(t_data *data)
{
    int i;
    int j;
    size_t k;
    int count;
    t_cmd *tmp;
    char  **tab;
  
    tmp = data->cmd;
    t_cmd *tmp1 = data->cmd;
    tab = (char **)malloc(sizeof(char *) * (count_pipes(data) +  1));
    if (!tab)
        return (NULL);  
    k = 0;
    while (k < count_pipes(data))
    {
        count = 0;
        while (tmp && tmp->type != PIPE)
        {
            i = 0;
            while (tmp->str && tmp->str[i])
            {
                count++;
                i++;
            }
            tmp = tmp->next;
        }
        tab[k] = (char *)malloc(sizeof(char) * (count + 1));
        if (!tab[k])
            return (free_tab(tab));
        k++;
    } 
    i = 0;
    j = 0;
    while (i < count_pipes(data))
    {
        k = 0;
        while (tmp1)
        {
            j = 0;
            while(tmp1->str && tmp1->str[j]){
                tab[i][k++] = tmp1->str[j++];
            }
            if (tmp1->type == PIPE)
            {tab[i][k] = '\0';
                tmp1 = tmp1->next;
                break ;
            }
    printf("line : %s\n", tab[i]);
            tmp1 = tmp1->next;
        }
        tab[i][k] = '\0';
        i++;
    }
    tab[i] = 0;
    return(tab);
}



static char	**ft_cat(char **str, const char *s, char c, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < len)
	{
		k = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			str[i][k] = s[j];
			j++;
			k++;
		}
	str[i][k] = '\0';
	i++;
	}
	str[i] = 0;
	return (str);
}