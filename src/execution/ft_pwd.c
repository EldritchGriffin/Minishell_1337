/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:00:46 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/28 09:14:17 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_data *data)
{
	if (getcwd(data->path, PATH_MAX))
	{
		ft_putendl_fd(data->path, data->exc->out_file);
		x_st = 0;
		return (1);
	}
	x_st = 1;
	return (0);
}