/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:09:27 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/24 05:13:29 by zrabhi           ###   ########.fr       */
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
		return ;
	}
	if (tmp->next)
		tmp = tmp->next;
	if (chdir(tmp->next->str) == -1)
		return (printf("an error occurred with chdir\n"), (void)0);
}
