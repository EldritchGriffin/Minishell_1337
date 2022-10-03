/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/03 05:19:42 by zrabhi           ###   ########.fr       */
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
	else if (w_data)
		*j = -1;
}

static void	ft_check_vb(int check, char **str, char *cmd)
{
	if (!check)
		*str = ft_join_exc(*str, cmd);
}

static int	check_return(int i, char *str, int *in_file, int her_file)
{
	if (i == -1)
		return (perror(str), 0);
	if (i == 0)
		*in_file = her_file;
	return (1);
}

char	*get_redirection(t_exc **exc, int her_file, int *result)
{
	t_vb	vb;
	int		i;
	char	*str;

	initilazie_data(&vb.i, &vb.j, &str, 0);
	while ((*exc)->str[++vb.i])
	{
		vb.j = -1;
		vb.check = 0;
		while (get_strredir(++vb.j))
		{
			if (!ft_strcmp((*exc)->str[vb.i], get_strredir(vb.j)))
			{
				vb.check = 1;
				if (!check_redirfile((*exc)->str[vb.i + 1], &vb.check, &vb.i))
					break ;
				i = ft_open(&(*exc)->out_file, &(*exc)->in_file, \
				vb.j, (*exc)->str[vb.i]);
				if (!check_return(i, (*exc)->str[vb.i], &(*exc)->in_file, her_file))
					return (NULL);
				*result = 1;
			}
		}
		ft_check_vb(vb.check, &str, (*exc)->str[vb.i]);
	}
	return (str);
}
