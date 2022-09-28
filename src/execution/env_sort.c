/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:09:16 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/28 05:24:02 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

size_t	envtab_len(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	env_len(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i += ft_strlen(tmp->key);
		i += ft_strlen(tmp->value);
		i += 4;
		tmp = tmp->next;
	}
	return (i);
}

char	*env_to_str(t_env *env, t_data *data)
{
	t_env	*tmp;
	char	*str;
	int		size;
	int		i;
	int		j;
	int		k;

	tmp = env;
	i = 0;
	j = 0;
	k = 0;
	size = env_len(env);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (tmp)
	{
		j = 0;
		k = 0;
		while (tmp->key[j])
			str[i++] = tmp->key[j++];
		if (tmp->value)
		{
			str[i++] = '=';
			str[i++] = '"';
		}
		while (tmp->value && tmp->value[k])
			str[i++] = tmp->value[k++];
		if (tmp->value)
			str[i++] = '"';
		if (tmp->next != NULL)
			str[i++] = '\n';
		tmp = tmp->next;
	}
	str[i] = '\0';
	return (str);
}

static void	sort_env(char **tab, int tab_len)
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
