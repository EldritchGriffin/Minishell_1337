/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 02:44:03 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/14 18:55:53 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    print_env(t_env *env)
{
	t_env	*tmp;
	char *str;
	tmp = env;
	if (!tmp)
	{
		printf("its true \n\n\n");
		tmp = env_list(&str);
	}
	while(tmp)
	{
		if (tmp->value)
			printf("%s=%s\n",tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void    add_back_env(t_env  **env, t_env    *new_node)
{
	t_env   *tmp;
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

t_env   *new_node_env(char  *key,   char    *value)
{
	t_env   *new_node;

	new_node =  malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

static char	 **fill_extren_env(void)
{	
	char **env;
	
	env = malloc(sizeof(char *) * 5);
	if(!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	env[1] = ft_strdup("PWD=/Users/zrabhi/Desktop/Minishell");
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = 0;	
	return (env);
}
t_env   *env_list(char  **envp)
{
	char    **spltd;
	int     i;
	t_env   *env;
	if (!envp[0])
		envp = fill_extren_env(); 
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


