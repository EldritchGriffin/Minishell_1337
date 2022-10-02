/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:41:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/01 15:00:20 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	check_one(t_cmd *node, t_cmd *node_next)
{
	if (((node->type == D_QUOTES || node->type == S_QUOTES
				|| node->type == WORD)) && (node_next->type == D_QUOTES
			|| node_next->type == S_QUOTES || node_next->type == WORD))
		return (true);
	return (false);
}

int	search_spc_node(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = (*cmd);
	while (tmp)
	{
		if (tmp->type == SPC)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

char	*trim_quote(char *str)
{
	char	*lstr;
	char	rtr[2];

	if (!str)
		return (NULL);
	rtr[0] = get_quote(str[0]);
	rtr[1] = '\0';
	lstr = ft_strtrim(str, rtr);
	if (!lstr)
		return (NULL);
	return (lstr);
}

int	ft_open(int *out_file, int *in_file, int j, char *str)
{
	if (j == 0)
		return (*out_file = open(str, O_RDWR | O_APPEND | O_CREAT, 0777), 1);
	else if (j == 3)
		return (*out_file = open(str, O_CREAT | O_TRUNC | O_RDWR, 0644), 1);
	else if (j == 2)
	{
		if (access(str, F_OK | R_OK))
			return (*in_file = -1, perror("access ")
				, -1);
		return (*in_file = open(str, O_RDONLY), 1);
	}
	return (0);
}

