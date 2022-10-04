/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:54:15 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 17:00:54 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	initalize_childs(t_data *data)
{
	data->pps = malloc(sizeof(t_pipe));
	if (!data->pps)
		return (mini_perror("Memory"), (void)0);
	data->tokens = malloc(sizeof(t_types));
	if (!data->pps)
		return (mini_perror("Memory"), (void)0);
}

void	initialize(t_data *data, char **line)
{
    data->cmd = NULL;
	data->exc = NULL;
	*line = NULL;
}