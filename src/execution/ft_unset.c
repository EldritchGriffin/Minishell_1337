/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:55 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/03 18:16:47 by aelyakou         ###   ########.fr       */
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
		if(tmp->type != WORD && tmp->type != D_QUOTES && tmp->type != S_QUOTES)
			break;
		str = tmp->str;
		if(tmp->type == D_QUOTES || tmp->type == S_QUOTES)
			str = rmv_quotes(tmp->str);
		while(env)
		{
			if(env->next)
			{
				if (!ft_strcmp(env->next->key, str))
					break;
			}
			env = env->next;
		}
		if(!env)
			break;
		free(env->next->key);
		free(env->next->value);
		free(env->next);
		env->next = env->next->next;
		tmp = tmp->next;
	}	
}
