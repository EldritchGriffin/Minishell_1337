/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 02:30:39 by aelyakou          #+#    #+#             */
/*   Updated: 2022/08/25 10:14:59 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_lstdelone(t_ptr *lst)
{
	if (!lst)
		return ;
	free(lst->ptr);
	lst->ptr = NULL;
	free(lst);
	lst = NULL;
}
