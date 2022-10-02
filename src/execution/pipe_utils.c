/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 08:52:51 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/02 15:33:45 by aelyakou         ###   ########.fr       */
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

int	redirect_inpipes(t_exc	*tmp, int status, t_data	*data, int i)
{
	if (tmp->in_file != 0)
	{
		if (i != 0)
		{
			dup2(tmp->in_file, data->pps->p_fd[i - 1][0]);
		}
		else
		{
			status = dup(STDIN_FILENO);
			dup2(tmp->in_file, STDIN_FILENO);
		}
	}
	return (status);
}
