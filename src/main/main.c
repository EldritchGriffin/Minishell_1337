/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/24 04:21:53 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//TODO main function will have all our structs assigned into t_data
static void	initialize(t_data *data, char **line)
{
	data->cmd = NULL;
	data->exc = NULL;
	data->ptrs = NULL;
	*line = NULL;
}

int	main(int ac, char **av, char	**envp)
{
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;
	data.pps = malloc(sizeof(t_pipe));
	initialize(&data, &line);
	while (1)
	{
		data.env = env_list(envp);
		line = ft_strtrim(readline("Guest@\033[0;35mMinishell$: \033[0;37m")\
				, " ");
		if (!line)
		{
			free(line);
			break ;
		}
		if (line && line[0])
		{
			add_history(line);
			ft_shell(line, &data, data.env, envp);
			initialize(&data, &line);
		}
	}
	ft_putstr_fd("\b\b  \b\bexit\n", 2);
}
