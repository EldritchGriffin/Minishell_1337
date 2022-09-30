/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:20:19 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/30 09:16:15 by aelyakou         ###   ########.fr       */
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
		free(current->str);
		free(current);
	}
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
		free(current->flg);
		free(current);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*current;

	tmp = env;
	while (tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
	}
}
