/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 03:13:13 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/30 08:19:37 by aelyakou         ###   ########.fr       */
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
	int		status;
	int		i;
	int		check;
	int		j;

	check = 0;
	i = 0;
	tmp = exc;
	pids = malloc(sizeof(int) * (data->pps->p_c + 1));
	if (data->pps->p_c)
		data->pps->p_fd = create_pipes(data->pps->p_c);
	while (i <= data->pps->p_c && tmp)
	{
		if (rederection_check(&tmp, her_file))
		{
			if(tmp->in_file == -1)
				return ;
			if (tmp->in_file != 0)
			{
				if(i != 0)
				{
					dup2(tmp->in_file, data->pps->p_fd[i][0]);
					close(tmp->in_file);
				}
				else
				{
					status = dup(STDIN_FILENO);
					dup2(tmp->in_file, STDIN_FILENO);
					close(tmp->in_file);
				}

			}
			if (tmp->out_file != 1)
			{
				dup2(tmp->out_file, data->pps->p_fd[i][1]);
				close(tmp->out_file);
			}
		}
		pids[i] = fork();
		if(pids[i])
			ignore_signal();
		if (pids[i] == 0)
		{
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
			if(!identify_builtin(data, tmp))
				;
			else
				{
					if(execve(get_path(tmp->str, data, &check), tmp->str, envp) == -1)
					{
						x_st = 127;
						printf  ("Minishell : %s: command not found\n", tmp->str[0]);
					}
				}
			exit(x_st);
		}
		tmp = tmp->next;
		i++;
	}
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
        x_st = WEXITSTATUS(status);
	signals_handler();
}