/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:41:35 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/01 02:52:39 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*rmv_quotes(char	*str)
{
	char	*str1;

	str1 = ft_strdup(str);
	ft_strlcpy(str1, str + 1, (ft_strlen(str) - 1));
	return(str1);
}

void    ft_echo(t_data  *data)
{
	t_cmd   *tmp;
	char    *prnt;
	tmp = data->cmd->next->next;

	while(tmp)
	{
		if(tmp->type != WORD && tmp->type != D_QUOTES && tmp->type != S_QUOTES)
			break;
		prnt = tmp->str;
		if(tmp->type == D_QUOTES || tmp->type == S_QUOTES)
			prnt = rmv_quotes(tmp->str);
		printf("%s",prnt);
		tmp = tmp->next;
		if(tmp)
		{
			if(tmp->type == WORD || tmp->type == D_QUOTES || tmp->type == S_QUOTES) //FIXME problem with spaces between nodes that have no spaces between them (example: echo "hello""world");
				printf(" ");
		}

	}
	printf("\n");
}

t_env	*fill_export(char	**spltd)
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
	while(tmp)
	{
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
		printf("here\n");
		free(env->next->key);
		free(env->next->value);
		free(env->next);
		env->next = env->next->next;
		tmp = tmp->next;
	}	
}

int    identify_builtin(t_data *data)
{
	if(!data->cmd)
		return (1);
	if(!ft_strcmp(data->cmd->str, "echo"))
		return(ft_echo(data), 0);
	// if(!ft_strcmp(data->cmd->str, "cd"))
	//     return(ft_cd(data), 0);
	// if(!ft_strcmp(data->cmd->str, "pwd"))
	//     return(ft_pwd(data), 0);
	if(!ft_strcmp(data->cmd->str, "export"))
	    return(ft_export(data), 0);
	if(!ft_strcmp(data->cmd->str, "unset"))
	    return(ft_unset(data), 0);
	if(!ft_strcmp(data->cmd->str, "env"))
		return(print_env(data->env), 0);
	if(!ft_strcmp(data->cmd->str, "exit"))
		return(exit(0), 0); // TODO free_all_before_exiting
		
	return (1);
}