/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:09:27 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/25 21:56:42 by aelyakou         ###   ########.fr       */
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
		return (printf ("(%s) No such file or directory\n", tmp->next->str), (void)0);
}
