/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:23:54 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/17 18:06:12 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char   *check_expanding(char *str, t_data *data)
{
    t_env *tmp;
    
    tmp = data->env;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, str + 1))
            return (str = ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (str);
}

int     here_doc(t_cmd *delemiter, t_data *data)
{
    int fd[2];
    int i;
    char *str;
    char new_line[2];
   
   
   
    new_line[0] = '\n';
    new_line[1] = '\0';
    pipe(fd);
    i = 0;
    while (1)
    {
        str = readline("> ");
        if (delemiter->type != D_QUOTES || delemiter->type != S_QUOTES)
            str = check_expanding(str, data);
        if (!ft_strncmp(delemiter->str, str, ft_strlen(str)))
                break ;
        str = ft_strjoin(str, new_line);
        write(fd[1], str, ft_strlen(str));
        i++;
    }
    return (fd[0]);
}