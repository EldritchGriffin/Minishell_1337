/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:28:09 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/29 05:20:11 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_count_pipes(t_data *data)
{
	int	pipe;
	t_cmd	*tmp;

	tmp = data->cmd;
	pipe = 1;
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
