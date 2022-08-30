/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 04:07:36 by aelyakou          #+#    #+#             */
/*   Updated: 2022/08/22 21:37:09 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_ptr	*ft_lstnew(void *content)
{
	t_ptr	*head;

	head = (t_ptr *)malloc(sizeof(t_ptr));
	if (!head)
		return (NULL);
	head->ptr = content;
	head->next = NULL;
	return (head);
}
