/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:55 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/04 17:06:29 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_null(t_env	*env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next->next)
		tmp = tmp->next;
	free(tmp->next->key);
	if (tmp->next->value)
		free(tmp->next->value);
	free(tmp->next);
	tmp->next = NULL;
}

t_env	*find_node(char	*str, t_data	*data)
{
	t_env	*env;
	t_env	*node;

	env = data->env;
	if (!ft_strcmp(env->key, str))
		return (node = data->env, data->env = env->next, node);
	while (env->next)
	{
		if (!ft_strcmp(env->next->key, str))
			return (node = env->next, env->next = env->next->next, node);
		env = env->next;
	}
	if (!ft_strcmp(env->key, str))
	{
		set_null(data->env);
		return (NULL);
	}
	return (NULL);
}

void	free_node(t_env	*node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	ft_unset(t_exc	*cmd, t_data *data)
{
	int		i;
	t_env	*node;

	i = 1;
	if (!data->env)
		return (g_xst = 0, (void)0);
	while (cmd->str[i])
	{
		if (!check_identifier(cmd->str[i]))
		{
			node = find_node(cmd->str[i], data);
			if (node)
				free_node(node);
		}
		else
		{
			g_xst = 1598;
			ft_putstr_fd("invalid identifier \n", 2);
		}
		i++;
	}
	if (g_xst == 1598)
		g_xst = 1;
	else
		g_xst = 0;
}
