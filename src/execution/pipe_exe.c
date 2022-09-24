/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:13:13 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/24 05:17:55 by zrabhi           ###   ########.fr       */
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

//FIXME function has more than 25 lines
void	exec_pipes(t_exc *exc, t_data *data, int her_file, char **envp)
{
	t_exc	*tmp;
	int		*pids;
	int		i;
	int		j;

	i = 0;
	tmp = exc;
	pids = malloc(sizeof(int) * (data->pps->p_c + 1));
	if (data->pps->p_c)
		data->pps->p_fd = create_pipes(data->pps->p_c);
	while (i <= data->pps->p_c && tmp)
	{
		if (rederection_check(&tmp, her_file))
		{
			close(data->pps->p_fd[i][1]);
			dup2(tmp->out_file, data->pps->p_fd[i][1]);
			close(tmp->out_file);
		}
		pids[i] = fork();
		if (pids[i] == 0)
		{
			j = -1;
			while (++j < data->pps->p_c)
			{
				if ((j != i && j + 1 != i) || i == 0)
					close(data->pps->p_fd[j][0]);
				if (i == data->pps->p_c || i != j)
					close(data->pps->p_fd[j][1]);
			}
			if (i != 0)
			{
				dup2(data->pps->p_fd[i - 1][0], STDIN_FILENO);
				close(data->pps->p_fd[i - 1][0]);
			}
			if (i != data->pps->p_c)
			{
				dup2(data->pps->p_fd[i][1], STDOUT_FILENO);
				close(data->pps->p_fd[i][1]);
			}
			execve(get_path(tmp->str, data), tmp->str, envp);
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
		i++;
	}
	i = -1;
	while (++i < data->pps->p_c)
	{
		close(data->pps->p_fd[i][0]);
		close(data->pps->p_fd[i][1]);
	}
	i = -1;
	while (++i <= data->pps->p_c)
		wait(NULL);
}