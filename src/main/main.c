/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/05 02:20:56 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	updt_shlvl(t_data	*data)
{
	int		i;
	int		lvl;
	char	**spltd;
	char	*tmp;

	i = -1;
	spltd = NULL;
	while (data->envp[++i])
	{
		if (!ft_strncmp(data->envp[i], "SHLVL", 5))
		{
			spltd = ft_split(data->envp[i], '=');
			free(spltd[1]);
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
	if (spltd && spltd[0])
		free_tab(spltd);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*line;

	(void)ac;
	data.avm = av;
	data.envp = envp;
	initalize_childs(&data);
	initialize(&data, &line);
	updt_shlvl(&data);
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
	free_all(&data);
}
