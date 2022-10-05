/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:08:11 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/04 18:05:32 by aelyakou         ###   ########.fr       */
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
			if(!tmp->value)
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
		printf("tab[count] ============ %d", tab[count] );
		spltd[count] = malloc(sizeof(char) * (tab[count] + 1));
		spltd[count][tab[count]] = 0;
		count--;
	}
	spltd = fill_spltd(var, spltd, word_counter(var));
	return (join_expnd(spltd, env, word_counter(var)));
}

void	check_variables(t_cmd	*tmp, t_data	*data)
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
		tmp->str = find_var(tmp->str, data->env);
		tmp->type = WORD;
	}
}