/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:23:54 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/29 07:07:43 by aelyakou         ###   ########.fr       */
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
static void ft_join(char **str)
{
	char *tmp;
	
	tmp = *str;
	*str = ft_strjoin(*str, "\n");
	free(tmp);
}
int	here_doc(t_cmd *delemiter, t_data *data)
{
	int		fd[2];
	int		pid;
	int		status;
	char	*str;
	int		her_doc;

	pid = fork();
	pipe(fd);
	if(pid)
		ignore_signal();
	if(pid == 0)
	{
		rl_catch_signals = 1;
		signal(SIGINT, &handler);
		while (1)
		{
			str = readline("> ");
			if (delemiter->type != D_QUOTES || delemiter->type != S_QUOTES)
			{
				if (str && str[0] == '$')
					str = check_expanding(str, data);
			}
			if (!str)
			{
				break ;
			}
			if (!ft_strcmp(delemiter->str, str))
				break ;
			ft_join(&str);
			write(fd[1], str, ft_strlen(str));
		}
		close(fd[1]);
		free(str);
		x_st = 0;
		exit(x_st);
	}
	wait(&status);
	close(fd[1]);
	signals_handler();
	if (WIFEXITED(status)) 
	{
        x_st = WEXITSTATUS(status);
		if(x_st == 1)
			return(-1);
	}
	return (fd[0]);
}