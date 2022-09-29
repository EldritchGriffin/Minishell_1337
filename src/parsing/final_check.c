/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 05:39:17 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/29 14:34:06 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int operator_handler(char *str, int type)
{
	if (type == PIPE)
	{
		if ((ft_strcmp("|", str) < 0) && ft_strlen(str) != 1)
			return (0);
	}
	else if (type == I_REDIRECTION)
	{
		if ((ft_strcmp("<", str) < 0) && ft_strlen(str) != 1)
			return (0);
	}
	else if (type == I_REDIRECTION)
	{
		if ((ft_strcmp(">", str) < 0) && ft_strlen(str) != 1)
			return (0);
	}
	else if(!operator_handler2(str, type))
			return (0);
	return (1);
}

int	check_operatrs_first(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmd;
	if ((tmp->opr && !tmp->next) || (tmp->opr && tmp->next->type == SPC && !tmp->next->next))
		return (x_st = 258, mini_perror("SPC"), 0);
	return (1);
}

int	check_operators_sec(t_data *data)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = data->cmd;
	if (tmp->type == PIPE || (tmp->type == PIPE && tmp->next->type == WORD))
		return (x_st = 258, mini_perror("PIPE"), 0);
	while (tmp)
	{
		if (tmp->opr)
		{
			if (!ft_cases1(tmp))
				return (x_st = 258, unexpected_token(tmp->str[0]), 0);
			if ((tmp->next && !tmp->next->opr && !tmp->next->next))
				return (x_st = 258, mini_perror("SPC"), 0);
			else if (!operator_handler(tmp->str, tmp->type))
				return (x_st = 258, unexpected_token(tmp->str[0]), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}