/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:20:31 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/30 13:24:28 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	*char_counter(char *var, int count)
{
	int		*tab;
	int		i;
	int		j;
	int		stat;

	i = -1;
	j = 0;
	tab = malloc(sizeof(int) * (count + 1));
	stat = 0;
	while (var[++i])
	{
		if (var[i] == '$')
		{
			if (i && !stat)
				tab[count--] = j;
			char_check(var, &i, &j);
			tab[count--] = j;
			j = -1;
			stat = 1;
		}
		else
			stat = 0;
		j++;
	}
	return (tab[count] = j, tab);
}

void	char_check(char	*var, int	*i, int	*j)
{
	(*i)++;
	(*j) = 1;
	while (ft_isalnum(var[(*i)]) || var[(*i)] == '_')
	{
		(*i)++;
		(*j)++;
	}
	(*i)--;
}

char	**fill_spltd(t_expnd	expnd)
{
	int	stat;

	expnd.i = -1;
	expnd.j = 0;
	stat = 0;
	expnd.count--;
	while (expnd.var[++expnd.i])
	{
		if (expnd.var[expnd.i] == '$')
			check_spltd(&expnd, &stat);
		else
		{
			stat = 0;
			expnd.spltd[expnd.count][expnd.j] = expnd.var[expnd.i];
		}
		expnd.j++;
	}
	if (!expnd.var[expnd.i] && !stat)
		expnd.spltd[expnd.count][expnd.j] = '\0';
	return (expnd.spltd);
}

char	*find_var(char *var, t_env *env)
{
	char	*str;
	t_env	*tmp;

	tmp = env;
	str = ft_strdup(var);
	ft_strlcpy(str, var + 1, ft_strlen(var));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
			return (var = ft_strdup(tmp->value), var);
		tmp = tmp->next;
	}
	var = ft_strdup("");
	return (var);
}

char	*join_expnd(char **spltd, t_env *env, int count)
{
	char	*str;

	str = ft_strdup("");
	count--;
	while (count >= 0)
	{
		if (spltd[count][0] == '$')
			spltd[count] = find_var(spltd[count], env);
		str = ft_strjoin(str, spltd[count]);
		count--;
	}
	return (str);
}
