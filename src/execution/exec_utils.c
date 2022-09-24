/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:58:59 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/24 05:10:54 by zrabhi           ###   ########.fr       */
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