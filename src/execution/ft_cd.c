/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:09:27 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/30 09:01:47 by aelyakou         ###   ########.fr       */
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
		str = ft_strjoin("/Users/", getenv(("USER")));
		chdir(str);
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
