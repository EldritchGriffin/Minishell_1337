/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:09:27 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/01 03:06:00 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd(t_data	*data)
{
	t_cmd	*tmp;
	char	*str;

	tmp = data->cmd;
	if (!tmp->next)
	{
		str = get_ev(data, "HOME");
		if(chdir(str) == -1)
		{
			perror(str);
			return (g_xst = 1, (void)0);
		}
		free(str);
		g_xst = 0;
		return ;
	}
	if (tmp->next)
		tmp = tmp->next;
	if (chdir(tmp->next->str) == -1)
	{
		printf ("(%s) No such file or directory\n", tmp->next->str);
		return (g_xst = 1, (void)0);
	}
	g_xst = 0;
}
