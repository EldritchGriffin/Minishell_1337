/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:53:22 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/05 21:51:19 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_closefiles(int *in_file, int *out_file)
{
	if (*in_file != 0)
		close(*in_file);
	if (*out_file != 1)
		close(*out_file);
}

static void	ft_return_fd(int *in_save, int *out_save, int stdin, int stdout)
{
	dup2(*in_save, stdin);
	close(*in_save);
	dup2(*out_save, stdout);
	close(*out_save);
}

void	exec(int pid, t_exc	*exc, char	*bin, char	**envp)
{
	int	status;

	if (pid == 0)
	{
		if (exc->in_file != 0)
			close(exc->in_file);
		if (exc->out_file != 1)
			close(exc->out_file);
		status = execve(bin, exc->str, envp);
		if (status == -1)
		{
			g_xst = 127;
			perror("Minishell ");
			exit(g_xst);
		}
	}
}

void	handle_exits(int status)
{
	if (WIFEXITED(status))
	{
		g_xst = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		ft_putstr_fd("\n", 1);
		g_xst = 130;
	}
}

void	exec_cmd(t_exc *exc, char *bin, char **envp)
{
	pid_t	pid;
	int		status;
	int		in_save;
	int		out_save;

	ft_dup(&in_save, &out_save);
	ft_dup2(&exc->in_file, &exc->out_file, \
			STDIN_FILENO, STDOUT_FILENO);
	status = 0;
	pid = fork();
	if (pid)
		ignore_signal();
	if (pid == -1)
	{
		perror("fork");
		g_xst = 1;
	}
	exec(pid, exc, bin, envp);
	waitpid(pid, &status, 0);
	handle_exits(status);
	signals_handler();
	ft_closefiles(&exc->in_file, &exc->out_file);
	ft_return_fd(&in_save, &out_save, STDIN, STDOUT);
}
