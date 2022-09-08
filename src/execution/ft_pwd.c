/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 05:35:38 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/08 05:51:19 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int     ft_pwd(void)
{
    char path[PATH_MAX]; //PATH_MAX : determines how many characters are allowed in a full pathname 1024
    
        
    if (getcwd(path, PATH_MAX))
    {
        ft_putendl_fd(path, 1);
        return (1);
    }
    return (0);
}