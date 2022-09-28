/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:58:59 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/28 05:35:55 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*rmv_quotes(char	*str)
{
	char	*str1;

	str1 = ft_strdup(str);
	ft_strlcpy(str1, str + 1, (ft_strlen(str) - 1));
	return (str1);
}
int check_identifier(char	*str)
{
	int i;

	i = 0;
	if(str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	while(str[++i])
	{
		if(str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
	}
	return (0);
}
