/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:28:09 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 16:00:22 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_count_pipes(t_data *data)
{
	int		pipe;
	t_cmd	*tmp;

	tmp = data->cmd;
	pipe = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe++;
		tmp = tmp->next;
	}
	return (pipe);
}

char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	check_return(int i, char *str, int *in_file, int her_file)
{
	if (i == -1)
		return (perror(str), 0);
	if (i == 0)
		*in_file = her_file;
	her_file = 0;
	return (1);
}
