/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:20:19 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/23 15:45:51 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_cmd(t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*current;

	tmp = data->cmd;
	while (tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free(current);
	}
	free(tmp);
}

void	free_exc(t_data *data)
{
	t_exc	*tmp;
	t_exc	*current;

	tmp = data->exc;
	while (tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free_tab(current->str);
		free(current->str);
		free(current);
	}
	free(tmp);
}

void	free_env(t_data *data)
{
	t_env	*tmp;
	t_env	*current;

	tmp = data->env;
	while (tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free(current);
	}
}
