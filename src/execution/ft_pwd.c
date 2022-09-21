/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:00:46 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/21 02:02:43 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int     ft_pwd(t_data *data)
{
    char path[PATH_MAX]; //PATH_MAX : determines how many characters are allowed in a full pathname 1024
     
    if (getcwd(path, PATH_MAX))
    {
        ft_putendl_fd(path, data->exc->out_file);
        return (1);
    }
    return (0);
}