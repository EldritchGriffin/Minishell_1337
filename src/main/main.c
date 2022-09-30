/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/30 03:03:36 by zrabhi           ###   ########.fr       */
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
	(void)av;
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
		line = ft_strtrim(readline("Guest@\033[0;35mMinishell$: \033[0;37m"), " ");
		if (!line)
			break ;
		if (line && line[0])
		{
			add_history(line);
			ft_shell(line, &data, data.env, envp);
			initialize(&data, &line);
			//system("leaks Minishell");
		}
	}
	ft_putstr_fd("\b\b  \b\bexit\n", STDERR);
}
