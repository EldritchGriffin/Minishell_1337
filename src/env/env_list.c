/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 02:44:03 by aelyakou          #+#    #+#             */
/*   Updated: 2022/08/29 09:42:50 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while(tmp)
	{
		if(tmp->value)
			printf("%s=%s\n",tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void    add_back_env(t_env  **env, t_env    *new_node)
{
	t_env   *tmp;
	if(!env || !new_node)
		return ;
	if(!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return ;
}

t_env   *new_node_env(char  *key,   char    *value)
{
	t_env   *new_node;

	new_node =  malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env   *env_list(char  **envp)
{
	char    **spltd;
	int     i;
	t_env   *env;

	spltd = ft_split(envp[0], '=');
	env = new_node_env(spltd[0], spltd[1]);
	free(spltd);
	i = 1;
	while(envp[i])
	{
		spltd = ft_split(envp[i], '=');
		add_back_env(&env, new_node_env(spltd[0], spltd[1]));
		free(spltd);
		i++;
	}
	return (env);
}