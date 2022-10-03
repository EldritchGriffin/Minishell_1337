/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:09:16 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/03 02:06:20 by zrabhi           ###   ########.fr       */
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

static void	initalize_data(int *i, int *j, int *k, int check)
{
	if (!check)
	{
		*i = 0;
		*j = 0;
		*k = 0;
	}
	if (check)
	{
		*j = 0;
		*k = 0;
	}
}

static char	*appent_to_str(t_env *tmp, t_vb vb, int k)
{
	char	*str;

	str = malloc(sizeof(char) * (env_len(tmp) + 1));
	if (!str)
		return (NULL);
	while (tmp)
	{
		initalize_data(&vb.i, &vb.j, &k, 1);
		while (tmp->key[vb.j])
			str[vb.i++] = tmp->key[vb.j++];
		if (tmp->value)
		{
			str[vb.i++] = '=';
			str[vb.i++] = '"';
		}
		while (tmp->value && tmp->value[k])
			str[vb.i++] = tmp->value[k++];
		if (tmp->value)
			str[vb.i++] = '"';
		if (tmp->next != NULL)
			str[vb.i++] = '\n';
		tmp = tmp->next;
	}
	str[vb.i] = '\0';
	return (str);
}

char	*env_to_str(t_env *env, t_data *data)
{
	t_env	*tmp;
	char	*str;
	t_vb	vb;
	int		k;

	tmp = env;
	initalize_data(&vb.i, &vb.j, &k, 0);
	str = appent_to_str(tmp, vb, k);
	return (str);
}
