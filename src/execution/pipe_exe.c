/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:13:13 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/21 20:04:31 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int check_pipes(t_exc   *exc)
{
    int cnt;
    t_exc   *tmp;

    cnt = 0;
    tmp = exc;
    while(tmp)
    {
        // if(tmp->next)
            cnt++;
        tmp = tmp->next;
    }
    printf("pipes = %d\n", cnt);
    return (cnt);
}