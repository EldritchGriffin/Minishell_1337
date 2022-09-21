/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:06:06 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/21 01:28:06 by zrabhi           ###   ########.fr       */
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
		if(!ft_strcmp(tmp->key, spltd[0]))
		{
			if(spltd[1])
				ft_strcat(tmp->value, spltd[1]);
			return	(true);
		}
		tmp = tmp->next;
	}
	add_back_env(&data->env, new_node_env(spltd[0], spltd[1]));
	return (true);
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
			spltd[0] = ft_substr(str, 0, i);
			break;
		}
	}
	if(!spltd[0])
		spltd[0] = ft_strdup(str);
	else
	{
		if(*mode)
			i++;
		spltd[1] = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
	}
	return (spltd);
}

static void	fill_export(char	*str, t_data	*data)
{
	bool	mode;
	t_env	*tmp;
	char	**spltd;
	int		i;

	tmp = data->env;
	spltd = malloc(sizeof(char	*) * 3);
	spltd[0] = NULL;
	spltd[1] = NULL;
	spltd[2] = NULL;
	spltd = splt(str, &mode, spltd);
	if(mode)
		return(append_env(data, spltd), (void)0);
	while(tmp)
	{
		if(!ft_strcmp(tmp->key, spltd[0]))
		{
			if(tmp->value)
				return;
			else if(!spltd[1])
				tmp->value = NULL;
			else
				tmp->value = ft_strdup(spltd[1]);
			return ;
		}
		tmp = tmp->next;
	}
	add_back_env(&data->env, new_node_env(spltd[0], spltd[1]));
}



void	ft_export(t_data	*data)
{
	t_cmd	*tmp;
	char	*str;
	int		i = 1;
	
	tmp = data->cmd->next;
	if(!tmp || data->exc->out_file != 1)
		return(sorted_env(data->env, data), (void)0);
	while (tmp)
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
