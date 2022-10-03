/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:15:46 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/03 01:32:25 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_join(char **str)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, "\n");
	free(tmp);
}

void	ft_join1(char **str)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, "\0");
	free(tmp);
}
