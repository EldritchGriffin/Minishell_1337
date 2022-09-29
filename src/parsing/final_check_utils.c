/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 05:16:27 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/29 05:17:36 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


int	ft_cases1(t_cmd *tmp)
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

int operator_handler2(char *str, int type)
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