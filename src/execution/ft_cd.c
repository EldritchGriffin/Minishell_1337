/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:09:27 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/28 09:12:32 by aelyakou         ###   ########.fr       */
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
		x_st = 0;
		return ;
	}
	if (tmp->next)
		tmp = tmp->next;
	if (chdir(tmp->next->str) == -1)
	{
		printf ("(%s) No such file or directory\n", tmp->next->str);
		return (x_st = 1, (void)0);
	}
	x_st = 0;
}
