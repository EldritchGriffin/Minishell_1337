/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 01:28:58 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/03 01:31:36 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_back_env(t_env **env, t_env	*new_node)
{
	t_env	*tmp;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return ;
}

t_env	*new_node_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	sorted_env(t_env *env, t_data *data)
{
	char	**str;
	char	*str_to_env;
	int		i;

	i = 0;
	str_to_env = env_to_str(env, data);
	str = ft_split(str_to_env, '\n');
	free(str_to_env);
	sort_env(str, envtab_len(str));
	while (str[i])
	{
		ft_putstr_fd("declare -x ", data->exc->out_file);
		ft_putendl_fd(str[i], data->exc->out_file);
		i++;
	}
	free_tab(str);
}
