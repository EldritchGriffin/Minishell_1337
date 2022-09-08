/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:59:54 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/04 18:47:43 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_cmd	*check_opt(t_cmd	*tmp, bool *n_opt)
{
	int	i;

	i = 1;
	*n_opt = false;
	while(tmp)
	{
		if(tmp->type == SPC)
			tmp = tmp->next;
		if(tmp->str[0] == '-')
		{
			while(tmp->str[i])
			{
				if(tmp->str[i] != 'n')
					return(tmp);
				i++;
			}
			*n_opt = true;
		}
		else
			return(tmp);
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
		if (tmp->type != WORD && tmp->type != D_QUOTES && tmp->type != S_QUOTES && tmp->type != VARIABLE)
			break ;
		printf("%s", tmp->str);
		tmp = tmp->next;
		if (tmp)
		{
			if (tmp->type == SPC)
				printf(" ");
		}
	}
	if (!n_opt)
		printf("\n");
}
