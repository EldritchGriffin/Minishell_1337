/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:15:55 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/25 02:46:14 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
// funtion has more than 25 line
void	ft_unset(t_data *data)
{
	t_env	*env;
	t_cmd	*tmp;
	char	*str;

	env = data->env;
	tmp = data->cmd->next;
	while (tmp)
	{
		env = data->env;
		if (tmp->type == SPC)
			tmp = tmp->next;
		if (tmp->type != WORD && tmp->type != D_QUOTES && tmp->type != S_QUOTES)
			break ;
		while (env)
		{
			if (env->next)
			{
				if (!ft_strcmp(env->next->key, tmp->str))
					break ;
			}
			env = env->next;
		}
		if (!env)
			break ;
		env->next = env->next->next;
		tmp = tmp->next;
	}	
}
