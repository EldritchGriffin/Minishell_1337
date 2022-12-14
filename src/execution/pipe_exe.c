/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:13:13 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/05 22:20:36 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	redirect_pipes(t_exc *tmp, int her_file, int i, t_data *data)
{
	int			status;

	if (rederection_check(&tmp, her_file))
	{
		if (tmp->in_file == -1)
			return (-1);
		redirect_inpipes(tmp, status, data, i);
		if (tmp->out_file != 1)
		{
			if (i != data->pps->p_c)
				dup2(tmp->out_file, data->pps->p_fd[i][1]);
			else
				dup2(tmp->out_file, STDOUT_FILENO);
		}
	}
	return (0);
}

void	handle_fds(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->pps->p_c)
	{
		if (j + 1 != i || i == 0)
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
}

void	restore_parent(int	*stds, int status, int	*pids, t_data	*data)
{
	int		i;

	dup2(stds[0], STDIN_FILENO);
	dup2(stds[1], STDOUT_FILENO);
	if (status == 1)
	{
		i = -1;
		close_fds(data);
		while (++i <= data->pps->p_c)
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				g_xst = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					ft_putstr_fd("\n", 1);
					g_xst = 130;
				}
			}
		}
		signals_handler();
	}
}

void	pipe_exe(int *pids, t_data	*data, t_exc *tmp, int i)
{
	int	status;

	if (pids[i] == 0)
	{
		handle_fds(data, i);
		if (!identify_builtin(data, tmp))
			;
		else
		{
			if (execve(get_path(tmp->str, data, &status),
					tmp->str, data->envp) == -1)
			{
				g_xst = 127;
				perror("Minishell ");
			}
		}
		exit(g_xst);
	}
}

void	exec_pipes(t_exc *exc, t_data *data, int her_file, char **envp)
{
	t_vars	pipe;

	pipe.i = 0;
	pipe.status = 1;
	pipe.tmp = exc;
	pipe.pids = malloc(sizeof(int) * (data->pps->p_c + 1));
	pipe.std = save_stds();
	if (data->pps->p_c)
		data->pps->p_fd = create_pipes(data->pps->p_c);
	while (pipe.i <= data->pps->p_c && pipe.tmp)
	{
		handle_loop(pipe, her_file, data);
		pipe.tmp = pipe.tmp->next;
		pipe.i++;
	}
	restore_parent(pipe.std, 1, pipe.pids, data);
	free(pipe.std);
	free(pipe.pids);
	free_pids(data->pps->p_fd, data);
}
