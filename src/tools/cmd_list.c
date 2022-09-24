/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 05:20:26 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/24 05:35:19 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_cmd	*new_node_cmd(char *str, t_tokens type, bool operator, t_data *data)
{
	t_cmd	*new_node;

	new_node = ft_malloc(sizeof(t_cmd), &data->ptrs);
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->type = type;
	new_node->opr = operator;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

static void	add_back(t_cmd **cmd, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!cmd || !new_node)
		return ;
	if (!*cmd)
	{
		*cmd = new_node;
		return ;
	}
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
	return ;
}

void	cmd_list(char *str, t_tokens token, bool operator, t_data *data)
{
	add_back(&data->cmd, new_node_cmd(str, token, operator, data));
}
