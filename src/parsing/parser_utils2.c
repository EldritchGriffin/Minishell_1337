/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 08:43:57 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/03 03:40:45 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_join_exc(char *str, char *cmd)
{
	char	*tmp;
	char	*lrt;

	lrt = ft_strjoin(str, cmd);
	free(str);
	tmp = lrt;
	lrt = ft_strjoin(lrt, ":");
	free(tmp);
	return (lrt);
}

int	exctab_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*get_strredir(int j)
{
	if (j == 0)
		return (APPND);
	else if (j == 1)
		return (HRDC);
	else if (j == 2)
		return (I_REDI);
	else if (j == 3)
		return (O_REDI);
	return (NULL);
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
	if (!str)
		return (result = 2);
	if (result == 1)
	{
		free_tab((*exc)->str);
		(*exc)->str = ft_split(str, ':');
	}
	free(str);
	return (result);
}
