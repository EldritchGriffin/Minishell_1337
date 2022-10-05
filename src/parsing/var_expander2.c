/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:08:11 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/05 22:44:28 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*find_var(char *var, t_env *env)
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
	free_tab(spltd);
	return (str);
}

char	*prep_expnd(char	*var, t_env *env, t_cmd *cmd)
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
		spltd[count] = ft_calloc(sizeof(char), (tab[count] + 1));
		spltd[count][tab[count]] = '\0';
		count--;
	}
	free(tab);
	spltd = fill_spltd(var, spltd, word_counter(var) - 1);
	return (join_expnd(spltd, env, word_counter(var)));
}

void	check_variables(t_cmd	*tmp, t_data	*data)
{
	if (!ft_strcmp(tmp->str, "$0"))
	{
		free(tmp->str);
		tmp->str = ft_strdup(data->avm[0]);
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
		tmp->str = find_var(tmp->str, data->env);
		tmp->type = WORD;
	}
}

void	fill_vp(char	*var,	t_vex	*vex,	char	***spltd, int *count)
{
	while (ft_isalnum(var[(*vex).i]) || var[(*vex).i] == '_')
		(*spltd)[(*count)][(*vex).j++] = var[(*vex).i++];
	(*spltd)[(*count)--][(*vex).j] = '\0';
	(*vex).i--;
	(*vex).j = 0;
	(*vex).s = 1;
}
