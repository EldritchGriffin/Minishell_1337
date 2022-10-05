/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:19 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/04 17:06:10 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*find_var(char *var, t_env *env)
{
	char	*str;
	t_env	*tmp;

	tmp = env;
	str = malloc(ft_strlen(var));
	ft_strlcpy(str, var + 1, ft_strlen(var));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
		{
			if (!tmp->value)
				return (var = ft_strdup(""));
			return (free(var), free(str), var = ft_strdup(tmp->value), var);
		}
		tmp = tmp->next;
	}
	free(var);
	free(str);
	var = ft_strdup("");
	return (var);
}

char	*join_expnd(char **spltd, t_env *env, int count)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	count--;
	while (count >= 0)
	{
		if (spltd[count][0] == '$')
			spltd[count] = find_var(spltd[count], env);
		tmp = str;
		str = ft_strjoin(str, spltd[count]);
		free(tmp);
		count--;
	}
	return (str);
}

static char	**fill_spltd(char *var, char **spltd, int count)
{
	int	i;
	int	j;
	int	stat;

	i = -1;
	j = 0;
	stat = 0;
	count--;
	while (var[++i])
	{
		if (var[i] == '$')
		{
			if (i && !stat)
				spltd[count--][j] = '\0';
			spltd[count][0] = '$';
			i++;
			j = 1;
			while (ft_isalnum(var[i]) || var[i] == '_')
			{
				spltd[count][j] = var[i++];
				j++;
			}
			spltd[count--][j] = '\0';
			i--;
			j = -1;
			stat = 1;
		}
		else
		{
			stat = 0;
			spltd[count][j] = var[i];
		}
		j++;
	}
	if (!var[i] && !stat)
		spltd[count][j] = '\0';
	return (spltd);
}

static int	*char_counter(char *var, int count, t_cmd *cmd)
{
	int		*tab;
	int		i;
	int		j;
	int		stat;

	i = -1;
	j = 0;
	tab = malloc(sizeof(int) * (count));
	stat = 0;
	while (var[++i])
	{
		if (var[i] == '$')
		{
			if (i && !stat)
				tab[count--] = j;
			i++;
			j = 1;
			while (ft_isalnum(var[i]) || var[i] == '_')
			{
				i++;
				j++;
			}
			tab[count--] = j;
			i--;
			j = -1;
			stat = 1;
		}
		else
			stat = 0;
		j++;
	}
	return (tab);
}

static int	word_counter(char	*var)
{
	int		i;
	int		count;
	int		stat;

	i = -1;
	stat = 1;
	count = 0;
	while (var[++i])
	{
		if (stat == 1 && var[i] != '$')
		{
			stat = 0;
			count++;
		}
		if (var[i] == '$')
		{
			count++;
			i++;
			while (var[i] == '_' || ft_isalnum(var[i]))
				i++;
			if (!var[i])
				break ;
			stat = 1;
			i--;
		}
	}
	return (count);
}

static char	*prep_expnd(char	*var, t_env *env, t_cmd *cmd)
{
	char	**spltd;
	int		count;
	int		*tab;

	count = word_counter(var);
	tab = char_counter(var, count - 1, cmd);
	spltd = malloc(sizeof(char *) * (count + 1));
	spltd[count] = NULL;
	count--;
	while (count >= 0)
	{
		spltd[count] = malloc(sizeof(char) * (tab[count] + 1));
		spltd[count][tab[count]] = 0;
		count--;
	}
	spltd = fill_spltd(var, spltd, word_counter(var));
	return (join_expnd(spltd, env, word_counter(var)));
}

void	var_expnd(t_data *data)
{
	t_cmd	*tmp;
	char	*str;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->type == SPC)
			tmp = tmp->next;
		if (tmp->type == VARIABLE)
		{
			if (!ft_strcmp(tmp->str, "$0"))
			{
				free(tmp->str);
				tmp->str = ft_strdup("Minishell");
				tmp->type = WORD;
			}
			else if (!ft_strcmp(tmp->str, "$?"))
			{
				free(tmp->str);
				tmp->str = ft_itoa(g_xst);
				tmp->type = WORD;
			}
			else
			{
				str = tmp->str;
				tmp->str = find_var(tmp->str, data->env);
				tmp->type = WORD;
			}
		}
		if (tmp->type == EXPND_VB)
		{
			str = tmp->str;
			tmp->str = prep_expnd(tmp->str, data->env, data->cmd);
			free(str);
			tmp->type = D_QUOTES;
		}
		tmp = tmp->next;
	}
}
