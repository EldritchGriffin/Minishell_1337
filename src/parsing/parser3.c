/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 13:10:36 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	int	check_redirfile(char *str, int *check, int *i)
{
	if (!str)
		return (*check = 0, 0);
	return ((*i)++, 1);
}

static void	initilazie_data(int *i, int *j, char **str, int w_data)
{
	if (!w_data)
	{
		*i = -1;
		*str = ft_strdup("");
	}
}

static void	initalize_data1(int *j, int *check)
{
	*j = -1;
	*check = 0;
}

static void	ft_check_vb(int check, char **str, char *cmd)
{
	if (!check)
		*str = ft_join_exc(*str, cmd);
}

char	*get_redirection(t_exc **exc, int her_file, int *result)
{
	t_vb	vb;
	char	*str;

	initilazie_data(&vb.i, &vb.j, &str, 0);
	while ((*exc)->str[++vb.i])
	{
		initalize_data1(&vb.j, &vb.check);
		while (get_strredir(++vb.j))
		{
			if (!ft_strcmp((*exc)->str[vb.i], get_strredir(vb.j)))
			{
				vb.check = 1;
				if (!check_redirfile((*exc)->str[vb.i + 1], &vb.check, &vb.i))
					break ;
				vb.k = ft_open(&(*exc)->out_file, &(*exc)->in_file, \
				vb.j, (*exc)->str[vb.i]);
				if (!check_return(vb.k, (*exc)->str[vb.i], \
				&(*exc)->in_file, her_file))
					return (NULL);
				*result = 1;
			}
		}
		ft_check_vb(vb.check, &str, (*exc)->str[vb.i]);
	}
	return (str);
}
