/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:20:19 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 16:54:44 by zrabhi           ###   ########.fr       */
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

void	free_all(t_data *data)
{
	free(data->pps);
	free_env(data->env);
	free(data->tokens);
	ft_putstr_fd("\b\b  \b\bexit\n", STDERR);
}
