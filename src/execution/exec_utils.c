/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:58:59 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/28 23:26:31 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
