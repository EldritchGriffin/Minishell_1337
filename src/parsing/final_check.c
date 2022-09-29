/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 05:39:17 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/29 01:02:30 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"



static int operator_handler2(char *str, int type)
{
	if (type == APPEND)
	{
		if ((ft_strcmp(">>", str) < 0) && ft_strlen(str) != 2)
			return (0);
	}
	else if (type == HERDOC)
	{
		if ((ft_strcmp("<<", str) < 0) && ft_strlen(str) != 2)
			return (0);
	}
	return (1);
}

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
	if (tmp->opr && !tmp->next)
		return (unexpected_token(tmp->str[0]), 0);
	return (1);
}
static int	ft_cases1(t_cmd *tmp)
{
	if ((tmp->next && tmp->next->opr))
		return (x_st = 258, 0);
	else if ((tmp->next && !tmp->next->opr) && (tmp->next->next && tmp->next->next->opr))
		return (x_st = 258, 0);
	else if ((tmp->next && !tmp->next->opr) && (tmp->next->next && !tmp->next->next->opr) 
			&& (tmp->next->next->next && tmp->next->next->next->opr))
		return (x_st = 258, 0);
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
			// if ((((tmp->next && tmp->next->opr) || (tmp->next && !tmp->next->opr) \
			// 	|| ((tmp->next->next && !tmp->next->next->opr && !tmp->next->next->type != D_QUOTES) || (tmp->next->next && tmp->next->next->opr)))
			// 		&& ((tmp->next->next->next && tmp->next->next->next->opr) || !tmp->next)))
			// 	return (unexpected_token(tmp->str[0]), 0);
			if (!ft_cases1(tmp))
				return (x_st = 258, unexpected_token(tmp->str[0]), 0);
			if ((tmp->next && !tmp->next->opr && !tmp->next->next))
				return (x_st = 258,mini_perror("SPC"), 0);
			else if (!operator_handler(tmp->str, tmp->type))
				return (x_st = 258, unexpected_token(tmp->str[0]), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}