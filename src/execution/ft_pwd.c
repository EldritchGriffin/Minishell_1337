/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:00:46 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/08 15:59:25 by aelyakou         ###   ########.fr       */
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