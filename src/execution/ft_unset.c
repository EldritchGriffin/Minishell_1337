/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:55 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/21 02:10:06 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_unset(t_data		*data)
{
	t_env	*env = data->env;
	t_cmd	*tmp = data->cmd->next;
	char	*str;

	while(tmp)
	{
		env = data->env;
		if(tmp->type == SPC)
			tmp = tmp->next;
		if(tmp->type != WORD && tmp->type != D_QUOTES && tmp->type != S_QUOTES)
			break;
		while(env)
		{
			if(env->next)
			{
				if (!ft_strcmp(env->next->key, tmp->str))
					break;
			}
			env = env->next;
		}
		if (!env)
			break;
		env->next = env->next->next;
		tmp = tmp->next;
	}	
}
