/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 13:59:22 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


static void	initialize(t_data *data, char **line)
{
	// data->pps = malloc(sizeof(t_pipe));
	// if (!data->pps)
	// 	return (mini_perror("Memory"), (void)0);
	// data->tokens = malloc(sizeof(t_types));
	// if (!data->pps)
	// 	return ((void)0);
	// data->pps->p_c = 0;
	// data->pps->p_fd = 0;
	// data->tokens->tmp_type = 0;
	// data->tokens->old_type = 0;
	// data->tokens->operator = false;
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

static void	free_all(t_data *data)
{
	free(data->pps);
	free_env(data->env);
	free(data->tokens);
	ft_putstr_fd("\b\b  \b\bexit\n", STDERR);
}

int	main(int ac, char **av, char **envp)
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
			break ;
		if (line && line[0])
		{
			add_history(line);
			ft_shell(line, &data, data.env, envp);
			initialize(&data, &line);
			// system("leaks Minishell");
		}
	}
	free_all(&data);
}
