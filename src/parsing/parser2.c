/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:28:09 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/27 20:56:54 by aelyakou         ###   ########.fr       */
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
	// free(tab);
	return (NULL);
}
