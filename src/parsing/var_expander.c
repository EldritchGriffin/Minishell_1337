/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:19 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/05 21:45:50 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	increment_two(int *a, int *b, int mode)
{
	if (!mode)
	{
		(*a)++;
		(*b)++;
	}
}

char	**fill_spltd(char *var, char **spltd, int count)
{
	t_vex	vex;

	vex.i = -1;
	vex.j = 0;
	vex.s = 0;
	while (var[++vex.i])
	{
		if (var[vex.i] == '$')
		{
			if (vex.i && !vex.s)
				spltd[count--][vex.j] = '\0';
			spltd[count][0] = '$';
			vex.i++;
			vex.j = 1;
			fill_vp(var, &vex, &spltd, &count);
		}
		else
		{
			vex.s = 0;
			spltd[count][vex.j++] = var[vex.i];
		}
	}
	return (spltd);
}

int	*char_counter(char *var, int count, t_cmd *cmd)
{
	int		*tab;
	t_vex	vex;

	vex.i = -1;
	vex.j = 0;
	tab = malloc(sizeof(int) * (count));
	vex.s = 0;
	while (var[++vex.i])
	{
		if (var[vex.i] == '$')
		{
			if (vex.i++ && !vex.s)
				tab[count--] = vex.j;
			vex.j = 1;
			while (ft_isalnum(var[vex.i]) || var[vex.i] == '_')
				increment_two(&vex.i, &vex.j, 0);
			tab[count--] = vex.j;
			vex.i--;
			vex.j = -1;
			vex.s = 1;
		}
		else if (++vex.j || 1)
			vex.s = 0;
	}
	return (tab);
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
		if (stat == 1 && var[i] != '$' && ++count)
			stat = 0;
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
			check_variables(tmp, data);
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
