/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/01 12:18:32 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	initialize(t_data *data, char **line)
{
	data->cmd = NULL;
	data->exc = NULL;
	*line = NULL;
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
	data.env = env_list(envp);
	while (1)
	{
		signals_handler();
		rl_catch_signals = 0;
		line = ft_strtrim(readline("Guest@Minishell$: "), " ");
		if (!line)
			break ;
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

