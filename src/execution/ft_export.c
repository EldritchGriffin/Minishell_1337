/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:06:06 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/26 05:29:23 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	int check_identifier(char	*str)
{
	int i;

	i = 0;
	if(str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	while(str[++i])
	{
		if(str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
	}
	return (0);
}

static	char	*get_key(char	*str, bool	*mode)
{
	int i;
	char	*key;

	i = 0;
	*mode = false;
	while(str[i] && str[i] != '=')
		i++;
	if(str[i] == '=' && str[i - 1] == '+')
		*mode = true;
	if(*mode)
		key = ft_substr(str, 0, i - 1);
	else
		key = ft_substr(str, 0, i);
	if(check_identifier(key))
	{
		printf("invalid identifier (%s)\n", key);
		free(key);
		return (NULL);
	}
	return (key);
}

static	char	*get_value(char	*str)
{
	int	i;
	char	*val;

	i = -1;
	while(str[++i])
	{
		if(str[i] == '=')
		{
			val = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
			return (val);
		}
	}
	return (NULL);
}

static void	append_env(t_data	*data, char	*key, char	*val)
{
	t_env	*tmp;
	char	*ptr;

	tmp = data->env;
	while(tmp)
	{
		if(!ft_strcmp(key, tmp->key))
		{
			if(!tmp->value)
				tmp->value = ft_strdup(val);
			else
			{
				ptr = tmp->value;
				tmp->value = ft_strjoin(tmp->value, ft_strdup(val));
				free(ptr);
			}
			return ;
		}
		tmp = tmp->next;
	}
	add_back_env(&data->env, new_node_env(ft_strdup(key), ft_strdup(val)));
}

static void	do_export(t_data	*data, char	*key, char	*val, bool mode)
{
	t_env	*tmp;

	tmp = data->env;
	if(mode)
	{
		append_env(data, key, val);
		return ;
	}
	while(tmp)
	{
		if(!ft_strcmp(key, tmp->key))
		{
			if(!val)
				return;
			free(tmp->value);
			tmp->value = ft_strdup(val);
			return ;
		}
		tmp = tmp->next;
	}
	if(val)
		add_back_env(&data->env, new_node_env(ft_strdup(key), ft_strdup(val)));
	else
		add_back_env(&data->env, new_node_env(ft_strdup(key), NULL));
}

void	ft_export(t_exc	*cmd, t_data	*data)
{
	int 	i;
	char	*key;
	char	*val;
	bool	mode;

	i = 1;
	if(!cmd->str[i])
		return (sorted_env(data->env, data), (void) 0);
	while(cmd->str[i])
	{
		key = get_key(cmd->str[i], &mode);
		if(key)
		{
			val = get_value(cmd->str[i]);
			do_export(data, key, val, mode);
			free(key);
			if(val)
				free(val);
		}
		i++;
	}
}
