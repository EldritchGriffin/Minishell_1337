/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 08:43:57 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/01 08:44:42 by zrabhi           ###   ########.fr       */
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