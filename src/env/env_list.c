/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 02:44:03 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/04 14:10:39 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_env(t_env *env, t_data *data)
{
	t_env	*tmp;
	char	*str;

	tmp = env;
	do_export(data, "_", "/usr/bin/env", false);
	if (!tmp)
	{
		return ;
	}
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, data->exc->out_file);
			ft_putstr_fd("=", data->exc->out_file);
			ft_putendl_fd(tmp->value, data->exc->out_file);
		}
		tmp = tmp->next;
	}
	g_xst = 0;
}

static char	**fill_extren_env(void)
{	
	char	**env;
	char	*tmp;

	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	env[1] = ft_strdup("PWD=/Users/zrabhi/Desktop/Minishell");
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = 0;
	return (env);
}

t_env	*env_list(char **envp)
{
	char	**spltd;
	char	**tmp;
	int		i;
	t_env	*env;

	tmp = envp;
	if (!tmp[0])
		tmp = fill_extren_env();
	spltd = ft_split(tmp[0], '=');
	env = new_node_env(spltd[0], spltd[1]);
	free(spltd);
	i = 1;
	while (tmp[i])
	{
		spltd = ft_split(tmp[i], '=');
		add_back_env(&env, new_node_env(spltd[0], spltd[1]));
		free(spltd);
		i++;
	}
	if (!envp[0])
		free_tab(tmp);
	return (env);
}

void	sort_env(char **tab, int tab_len)
{
	char	*tmp;
	int		i;
	int		sort;

	sort = 0;
	while (tab && sort == 0)
	{
		i = 0;
		sort = 1;
		while (i < tab_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				sort = 0;
			}
			i++;
		}
		tab_len--;
	}
}
