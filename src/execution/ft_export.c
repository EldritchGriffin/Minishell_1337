/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:06:06 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/03 18:43:05 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_env	*fill_export(char	**spltd)
{
	char	*key;
	char	*value;
	t_env	*new_node;
	int		i;

	i = 1;
	key = spltd[0];
	value = NULL;
	while(spltd[i])
	{
		if(i == 1)
			value = ft_strdup("");
		value = ft_strjoin(value, spltd[i]);
		if(spltd[i+1])
			value = ft_strjoin(value, "=");
		i++;
	}
	new_node = new_node_env(key, value);
	return (new_node);
}

void	ft_export(t_data	*data)
{
	t_cmd	*tmp;
	char	*str;
	char	**spltd;
	int		i = 1;
	
	tmp = data->cmd->next;
	if(!tmp)
		return(print_env(data->env), (void)0);
	while(tmp)
	{
        if (tmp->next && tmp->type == SPC)
			tmp = tmp->next;
		if(tmp->type != WORD && tmp->type != D_QUOTES && tmp->type != S_QUOTES)
			break;
		str = tmp->str;
		if(tmp->type == D_QUOTES || tmp->type == S_QUOTES)
			str = rmv_quotes(tmp->str);
		spltd = ft_split(str, '='); //TODO change the split approach since it makes a problem in the case of multiple consecutive assign tokens;
		add_back_env(&data->env ,fill_export(spltd));
		free(spltd);
		tmp = tmp->next;
	}
}
