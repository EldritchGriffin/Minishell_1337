/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:00:46 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/01 04:02:27 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_data *data)
{
	if (getcwd(data->path, PATH_MAX))
	{
		ft_putendl_fd(data->path, data->exc->out_file);
		g_xst = 0;
		return (1);
	}
	g_xst = 1;
	return (0);
}
