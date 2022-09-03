/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:58:59 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/03 17:59:32 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*rmv_quotes(char	*str)
{
	char	*str1;

	str1 = ft_strdup(str);
	ft_strlcpy(str1, str + 1, (ft_strlen(str) - 1));
	return(str1);
}