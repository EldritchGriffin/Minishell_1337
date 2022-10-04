/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 08:52:51 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/04 13:14:54 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_pipes(t_exc	*exc)
{
	int		cnt;
	t_exc	*tmp;

	cnt = 0;
	tmp = exc;
	while (tmp)
	{
		if (tmp->next)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = malloc(sizeof(int *) * count);
	while (++i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
	}
	return (pipes);
}

void	redirect_inpipes(t_exc	*tmp, int status, t_data	*data, int i)
{
	if (tmp->in_file != 0)
	{
		if (i != 0)
			dup2(tmp->in_file, data->pps->p_fd[i - 1][0]);
		else
			dup2(tmp->in_file, STDIN_FILENO);
	}
	return ;
}

int	*save_stds(void)
{
	int	*stds;

	stds = malloc(sizeof(int) * 2);
	stds[0] = dup(STDIN_FILENO);
	stds[1] = dup(STDOUT_FILENO);
	return (stds);
}

void	close_fds(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->pps->p_c)
	{
		close(data->pps->p_fd[i][0]);
		close(data->pps->p_fd[i][1]);
	}
}
