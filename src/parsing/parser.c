/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:53:30 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/28 23:33:40 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	replace_nodes(t_cmd **node, t_cmd **node_next, t_cmd **new_node)
{
	t_cmd	*tmp1;
	t_cmd	*tmp2;

	tmp1 = (*node);
	tmp2 = (*node_next);

	if (tmp1->prev)
		tmp1->prev->next = (*new_node);
	(*new_node)->prev = tmp1->prev;
	if (tmp2->next)
		tmp2->next->prev = (*new_node);
	(*new_node)->next = tmp2->next;
	free(tmp1->str);
	free(tmp1);
	free(tmp2->str);
	free(tmp2);
}

static void	recursion_call(t_cmd **node, t_cmd **node_next, t_cmd *new_node, t_data **data)
{
	replace_nodes(node, node_next, &new_node);
	join_unspaced(&new_node, &(new_node->next), data);
}

void	join_unspaced(t_cmd **node, t_cmd **node_next, t_data **data)
{
	char	*str1;
	char	*str2;
	char	*join;
	t_cmd	*new_node;

	if (!*node || !*node_next || (*node_next)->type == SPC)
		return ;
	if(!check_one(*node, *node_next))
		return ;
	join = ft_strjoin((*node)->str, (*node_next)->str);
	new_node = new_node_cmd(join, WORD, 0, *data);
	if ((!(*node)->prev && !(*node_next)->next) 
		|| (!(*node)->prev && (*node_next)->next))
	{
		if (!(*node)->prev && !(*node_next)->next)
		{
			(*data)->cmd = new_node;
			return ;
		}
		replace_nodes(node, node_next, &new_node);
		(*data)->cmd = new_node;  
		join_unspaced(&new_node, &(new_node->next), data);
	}
	else if ((*node)->prev && (*node_next)->next)
		recursion_call(node, node_next, new_node, data);
	else if ((*node)->prev && !(*node_next)->next)
		recursion_call(node, node_next, new_node, data);
   return ;
}