/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:06:06 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/08 15:59:31 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


//TODO EXPORT STILL UNFINISHED will fix after sortenv is all done (sigfaults in case of null)
static	bool	append_env(t_data	*data,char	**spltd)
{
	t_env	*tmp;

	tmp = data->env;
	while(tmp)
	{
		if(!ft_strcmp(tmp->key, spltd[1]))
		{
			if(spltd[2])
				ft_strjoin(tmp->value, spltd[2]);
			return	(true);
		}
		tmp = tmp->next;
	}
	return (false);
}

static	char	**splt(char	*str, bool *mode, char	**spltd)
{
	int		i;

	i = -1;
	while(str[++i])
	{
		if(str[i] == '=')
		{
			if(str[i - 1] == '+')
			{
				*mode = true;
				i--;
			}
			spltd[1] = ft_substr(str, 0, i);
			break;
		}
	}
	if(!spltd[1])
		spltd[1] = ft_strdup(str);
	else
	{
		if(*mode)
			i++;
		spltd[2] = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
	}
	return (spltd);
}

static void	fill_export(char	*str, t_data	*data)
{
	t_env	*new_node;
	bool	mode;
	char	**spltd;
	int		i;

	spltd = malloc(sizeof(char	*) * 2);
	spltd[1] = NULL;
	spltd[2] = NULL;
	spltd = splt(str, &mode, spltd);
	if(mode)
		return(append_env(data, spltd), (void)0);
	new_node = new_node_env(spltd[1], spltd[2]);
	add_back_env(&data->env, new_node);
}

void	ft_export(t_data	*data)
{
	t_cmd	*tmp;
	char	*str;
	int		i = 1;
	
	tmp = data->cmd->next;
	if(!tmp)
		return(sorted_env(data->env, data), (void)0);
	while(tmp)
	{
        if (tmp->next && tmp->type == SPC)
			tmp = tmp->next;
		if(tmp->type != WORD && tmp->type != D_QUOTES && tmp->type != S_QUOTES)
			break;
		str = tmp->str;
		if(tmp->type == D_QUOTES || tmp->type == S_QUOTES)
			str = rmv_quotes(tmp->str);
		fill_export(str, data);
		tmp = tmp->next;
	}
}
