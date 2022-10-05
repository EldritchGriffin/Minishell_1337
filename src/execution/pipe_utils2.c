/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:57:43 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/05 22:17:25 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_loop(t_vars	pipe, int her_file, t_data	*data)
{
	restore_parent(pipe.std, 0, pipe.pids, data);
	herdoc_handler(data, &her_file, pipe.i);
	pipe.status = redirect_pipes(pipe.tmp, her_file, pipe.i, data);
	if (pipe.status == -1)
		return ;
	pipe.pids[pipe.i] = fork();
	if (pipe.pids[pipe.i] == -1)
	{
		perror("fork");
		restore_parent(pipe.std, 1, pipe.pids, data);
		g_xst = 1;
		return ;
	}
	if (pipe.pids[pipe.i])
		ignore_signal();
	pipe_exe(pipe.pids, data, pipe.tmp, pipe.i);
}
