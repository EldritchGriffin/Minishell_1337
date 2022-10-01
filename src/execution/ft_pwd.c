/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:00:46 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/01 12:18:44 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_data *data)
{
	getcwd(data->path, PATH_MAX);
	ft_putendl_fd(data->path, data->exc->out_file);
	g_xst = 0;
	return (0);
}

