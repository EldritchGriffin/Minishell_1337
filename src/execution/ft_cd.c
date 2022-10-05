/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:09:27 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/05 00:47:49 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	cd_only(t_cmd	*tmp, t_data	*data)
{
	char	*str;

	if (!tmp->next)
	{
		str = get_ev(data, "HOME");
		do_export(data, "OLDPWD", getcwd(NULL, PATH_MAX), false);
		if (chdir(str) == -1)
		{
			g_xst = 1;
			perror(str);
		}
		else
			do_export(data, "PWD", getcwd(NULL, PATH_MAX), false);
		g_xst = 0;
		return (0);
	}
	return (1);
}

void	ft_cd(t_data	*data)
{
	t_cmd	*tmp;
	char	*str;

	tmp = data->cmd;
	if (!cd_only(tmp, data))
		return ;
	else
	{
		if (tmp->next)
			tmp = tmp->next;
		str = getcwd(NULL, PATH_MAX);
		do_export(data, "OLDPWD", str, false);
		free(str);
		if (chdir(tmp->next->str) == -1)
			return (perror("cd "), g_xst = 1, (void)0);
		else
		{
			str = getcwd(NULL, PATH_MAX);
			do_export(data, "PWD", str, false);
			free(str);
		}
		g_xst = 0;
	}
}
