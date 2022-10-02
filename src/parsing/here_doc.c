/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:23:54 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/02 15:01:17 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*check_expanding(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str + 1))
			return (str = ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (str);
}

static void	ft_join(char **str)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, "\n");
	free(tmp);
}

int	here_do(t_cmd	*delemiter, t_data	*data, int fd[])
{
	char	*str;

	ft_putstr_fd("> ", 1);
	str = get_next_line(0);
	str[ft_strlen(str) - 1] = '\0';
	// printf("%s\n", str);
	if (!str)
	{
		exit(1);
	}
	if (delemiter->type != D_QUOTES || delemiter->type != S_QUOTES)
	{
		if (str && str[0] == '$')
			str = check_expanding(str, data);
	}
	if (!ft_strcmp(delemiter->str, str))
		return (-1);
	ft_join(&str);
	write(fd[1], str, ft_strlen(str));
	free(str);
	return (0);
}

void	here_fork(int pid, t_cmd	*delemiter, t_data	*data, int fd[])
{
	if (pid == 0)
	{
		signal(SIGINT, &here_handler);
		while (1)
		{
			if (here_do(delemiter, data, fd) == -1)
				break ;
		}
		close(fd[1]);
		close(fd[0]);
		g_xst = 0;
		exit(g_xst);
	}
}

int	here_doc(t_cmd *delemiter, t_data *data)
{
	int		fd[2];
	int		pid;
	int		status;
	int		her_doc;

	pipe(fd);
	pid = fork();
	if (pid)
		ignore_signal();
	here_fork(pid, delemiter, data, fd);
	wait(&status);
	close(fd[1]);
	signals_handler();
	if (WIFEXITED(status))
	{
		g_xst = WEXITSTATUS(status);
		if (g_xst == 1)
			return (-1);
	}
	return (fd[0]);
}
