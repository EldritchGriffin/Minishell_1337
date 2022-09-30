/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:19 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/30 13:25:53 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	counter_check(int	*stat,	int	*i,	char	*var,	int	*count)
{
	if ((*stat) == 1 && var[(*i)] != '$')
	{
		(*stat) = 0;
		(*count)++;
	}
	if (var[(*i)] == '$')
	{
		(*count)++;
		(*i)++;
		while (var[(*i)] == '_' || ft_isalnum(var[(*i)]))
			(*i)++;
		if (!var[(*i)])
			return (1);
		(*stat) = 1;
		i--;
	}
	return (0);
}

int	word_counter(char	*var)
{
	int		i;
	int		count;
	int		stat;

	i = -1;
	stat = 1;
	count = 0;
	while (var[++i])
	{
		if (counter_check(&stat, &i, var, &count))
			break ;
	}
	return (count);
}

char	*prep_expnd(char *var, t_env *env)
{
	t_expnd	expnd;

	expnd.var = var;
	expnd.count = word_counter(var);
	expnd.tab = char_counter(var, expnd.count - 1);
	expnd.spltd = malloc(sizeof(char *) * (expnd.count + 1));
	expnd.spltd[expnd.count] = NULL;
	expnd.count--;
	while (expnd.count >= 0)
	{
		expnd.spltd[expnd.count]
			= malloc(sizeof(char) * (expnd.tab[expnd.count] + 1));
		expnd.count--;
	}
	expnd.count = word_counter(var);
	expnd.spltd = fill_spltd(expnd);
	return (join_expnd(expnd.spltd, env, word_counter(var)));
}

void	handle_vars(t_cmd	*tmp, t_data	*data)
{
	char	*str;

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
			free(str);
			tmp->type = WORD;
		}
	}
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
		handle_vars(tmp, data);
		if (tmp->type == EXPND_VB)
		{
			str = tmp->str;
			tmp->str = prep_expnd(tmp->str, data->env);
			free(str);
			tmp->type = D_QUOTES;
		}
		tmp = tmp->next;
	}
}
