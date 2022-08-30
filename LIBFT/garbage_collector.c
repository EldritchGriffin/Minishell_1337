/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:33:19 by aelyakou          #+#    #+#             */
/*   Updated: 2022/08/25 11:01:58 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void    *ft_malloc(int size, t_ptr **ptrs)
{
	void	*ptr;

	ptr = malloc(size);
	if(!ptr)
		return(NULL);
	ft_lstadd_back(ptrs, ft_lstnew(ptr));
	return(ptr);
}

void	destroy(t_ptr **lst)
{
	t_ptr	*temp;

	if (!lst)
		return ;
	temp = *lst;
	while (temp)
	{
		ft_lstdelone(temp);
		temp = temp->next;
	}
	*lst = NULL;
}
