/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:13:13 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/30 09:08:19 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	redirect_pipes(t_exc	*tmp, int her_file, int i, t_data	*data)
{
	int	status;

	if (rederection_check(&tmp, her_file))
	{
		if (tmp->in_file == -1)
			return (-1);
		status = redirect_inpipes(tmp, status, data, i);
		if (tmp->out_file != 1)
		{
			dup2(tmp->out_file, data->pps->p_fd[i][1]);
			close(tmp->out_file);
		}
	}
	return (status);
}

static void	handle_fds(t_data	*data, int i)
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

static void	restore_parent(int status, t_data	*data)
{
	int		i;
	t_exc	*tmp;

	dup2(status, STDIN_FILENO);
	i = -1;
	tmp = data->exc;
	while (++i < data->pps->p_c)
	{
		close(data->pps->p_fd[i][0]);
		close(data->pps->p_fd[i][1]);
	}
	i = -1;
	while (++i <= data->pps->p_c)
		wait(&status);
	if (WIFEXITED(status))
		g_xst = WEXITSTATUS(status);
	signals_handler();
}

static	void	pipe_exe(int	*pids, t_data	*data, t_exc	*tmp, int i)
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
				printf("Minishell : %s: command not found\n", tmp->str[0]);
			}
		}
		exit(g_xst);
	}
}

void	exec_pipes(t_exc *exc, t_data *data, int her_file, char **envp)
{
	t_exc	*tmp;
	int		*pids;
	int		status;
	int		i;

	i = 0;
	tmp = exc;
	pids = malloc(sizeof(int) * (data->pps->p_c + 1));
	if (data->pps->p_c)
		data->pps->p_fd = create_pipes(data->pps->p_c);
	while (i <= data->pps->p_c && tmp)
	{
		status = redirect_pipes(tmp, her_file, i, data);
		if (status == -1)
			return ;
		pids[i] = fork();
		if (pids[i])
			ignore_signal();
		pipe_exe(pids, data, tmp, i);
		tmp = tmp->next;
		i++;
	}
	restore_parent(status, data);
}
