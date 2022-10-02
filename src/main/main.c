/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/02 19:23:53 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	initialize(t_data *data, char **line)
{
	data->cmd = NULL;
	data->exc = NULL;
	*line = NULL;
}

void	updt_shlvl(t_data	*data)
{
	int		i;
	int		lvl;
	char	**spltd;
	char	*tmp;

	i = -1;
	while (data->envp[++i])
	{
		if (!ft_strncmp(data->envp[i], "SHLVL", 5))
		{
			spltd = ft_split(data->envp[i], '=');
			lvl = ft_atoi(spltd[1]);
			lvl++;
			tmp = spltd[0];
			spltd[0] = ft_strjoin(spltd[0], "=");
			free(tmp);
			spltd[1] = ft_itoa(lvl);
			tmp = ft_strjoin(spltd[0], spltd[1]);
			data->envp[i] = tmp;
		}
	}
}

int	main(int ac, char **av, char	**envp)
{
	t_data	data;
	char	*line;

	(void)ac;
	data.avm = av;
	data.envp = envp;
	data.pps = malloc(sizeof(t_pipe));
	if (!data.pps)
		return (mini_perror("Memory"), 0);
	data.tokens = malloc(sizeof(t_types));
	if (!data.pps)
		return (mini_perror("Memory"), 0);
	initialize(&data, &line);
	updt_shlvl(&data);
	data.env = env_list(envp);
	while (1)
	{
		signals_handler();
		rl_catch_signals = 0;
		line = ft_strtrim(readline("Guest@Minishell$: "), " ");
		if (!line)
		{
			break ;
		}
		if (line && line[0])
		{
			add_history(line);
			ft_shell(line, &data, data.env, envp);
			initialize(&data, &line);
			// system("leaks Minishell");
		}
	}
	free(data.pps);
	free_env(data.env);
	free(data.tokens);
	ft_putstr_fd("\b\b  \b\bexit\n", STDERR);
}

