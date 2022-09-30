/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_expander_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:25:28 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/30 13:25:44 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	check_spltd(t_expnd	*expnd, int	*stat)
{
	if ((*expnd).i && !*stat)
		(*expnd).spltd[(*expnd).count--][(*expnd).j] = '\0';
	(*expnd).spltd[(*expnd).count][0] = '$';
	(*expnd).i++;
	(*expnd).j = 1;
	while (ft_isalnum((*expnd).var[(*expnd).i])
		|| (*expnd).var[(*expnd).i] == '_')
	{
		(*expnd).spltd[(*expnd).count][(*expnd).j] = (*expnd).var[(*expnd).i++];
		(*expnd).j++;
	}
	(*expnd).spltd[(*expnd).count--][(*expnd).j] = '\0';
	(*expnd).i--;
	(*expnd).j = -1;
	*stat = 1;
}
