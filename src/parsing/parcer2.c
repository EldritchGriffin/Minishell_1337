/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:28:09 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/07 07:56:43 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int  ft_words(t_cmd *cmd, t_cmd *pipe)
{
    int i;
    int words;
    
    words = 0;
    i =  0;
    while (cmd)
    {
        if ((cmd->str[i] && cmd->type != PIPE) || (cmd->str[i] && !cmd->next))
        {
            words++;
            i++;
        }   
        cmd = cmd->next;
    }
    return (words);
}

static char     **ft_cat(char **tab, t_cmd *cmd, int len)
{
    int     i;
    int     j;
    int     k;
    t_cmd   *tmp;

    i = 0;
    j = 0;
    while (i < len)
    {
        k = 0;
        while (cmd)
        {
            j = 0;
            if (cmd->type == PIPE)
            {
                cmd = cmd->next;
                break ; 
            }
            while (cmd->str && cmd->str[j])
                tab[i][k++] = cmd->str[j++];
            cmd = cmd->next;
        }
        tab[i][k] = '\0';
        i++;    
    }
    tab[i] = 0;
    return(tab);
}

static size_t ft_count_pipes(t_data *data)
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

char **parse_args(t_data *data)
{
    char **str;
    t_cmd *tmp;
    int i;
    int j;
    int k;
   
    i = -1;
    str = (char **)malloc(sizeof(char *) * (ft_count_pipes(data) + 1));
    if (!str)
        return (NULL);
    tmp = data->cmd;
    while (++i < ft_count_pipes(data))
    {
        k = 0;
        while (tmp)
        {
            if (tmp->type == PIPE || !tmp->str)
            {
                tmp = tmp->next;
                break;
            }
            j = 0;
            k += ft_strlen(tmp->str);
            tmp = tmp->next;        
        }   
        str[i] = (char *)malloc(sizeof(char) * (k + 1));
        if (!str[i])
            return (free_tab(str)); 
    }
    return (ft_cat(str, data->cmd, ft_count_pipes(data)));
}