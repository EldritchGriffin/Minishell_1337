/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:59:54 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/24 05:14:12 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_cmd	*check_opt(t_cmd	*tmp, bool *n_opt)
{
	int	i;

	i = 1;
	*n_opt = false;
	while (tmp)
	{
		if (tmp->type == SPC)
			tmp = tmp->next;
		if (tmp->str[0] == '-')
		{
			while (tmp->str[i])
			{
				if (tmp->str[i] != 'n')
					return (tmp);
				i++;
			}
			*n_opt = true;
		}
		else
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_echo(t_data *data)
{
	t_cmd	*tmp;
	bool	n_opt;

	tmp = data->cmd->next;
	tmp = check_opt(tmp, &n_opt);
	while (tmp)
	{
		if (tmp->next && tmp->type == SPC)
			tmp = tmp->next;
		if (tmp->type != WORD && tmp->type != D_QUOTES
			&& tmp->type != S_QUOTES && tmp->type != VARIABLE)
			break ;
		ft_putstr_fd(tmp->str, data->exc->out_file);
		tmp = tmp->next;
		if (tmp)
		{
			if (tmp->type == SPC)
				ft_putstr_fd(" ", data->exc->out_file);
		}
	}
	if (!n_opt)
		ft_putstr_fd("\n", data->exc->out_file);
}
