/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/01 08:44:59 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	int	check_redirfile(char *str, int *check, int *i)
{
	if (!str)
		return (*check = 0, 0);
	return ((*i)++, 1);
}

char	*get_redirection(t_exc **exc, int her_file, int *result)
{
	int		i;
	int		j;
	int		check;
	char	*str;

	i = -1;
	str = ft_strdup("");
	while ((*exc)->str[++i])
	{
		j = -1;
		check = 0;
		while (get_strredir(++j))
		{
			if (!ft_strcmp((*exc)->str[i], get_strredir(j)))
			{
				check = 1;
				if (!check_redirfile((*exc)->str[i + 1], &check, &i))
					break ;
				if (!ft_open(&(*exc)->out_file, &(*exc)->in_file, \
				j, (*exc)->str[i]))
					if (her_file)
					(*exc)->in_file = her_file;
				*result = 1;
			}
		}
		if (!check)
			str = ft_join_exc(str, (*exc)->str[i]);
	}
	return (str);
}

int	rederection_check(t_exc **exc, int her_file)
{
	t_exc	*tmp;
	int		i;
	int		result;
	char	*str;

	result = 0;
	i = -1;
	tmp = *exc;
	str = get_redirection(&tmp, her_file, &result);
	if (result)
	{
		free_tab((*exc)->str);
		(*exc)->str = ft_split(str, ':');
	}
	free(str);
	return (result);
}
