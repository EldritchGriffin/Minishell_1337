/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:23:54 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/14 16:41:41 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"







void     here_doc(t_cmd *delemiter)
{
    int fd[2];
    int i;
    char *buf;
    char *str;
    char new_line[2];
    new_line[0] = '\n';
    new_line[1] = '\0';
    pipe(fd);
    i = 0;
    while (1)
    {
        str = readline("> ");
        
        str = ft_strjoin(str, new_line);
        if (ft_strncmp(str, delemiter->str, ft_strlen(delemiter->str)) == 0)
                break ;
        write(fd[1], str, ft_strlen(str));   
        i++;
    }
    // while(i-- != 0)
    // {
    //     buf = get_next_line(fd[0]);
    //     printf("%s", buf);
    //     //  ft_putendl_fd(buf, 0);
    // } 
    // printf("file read %s\n", buf);
}
