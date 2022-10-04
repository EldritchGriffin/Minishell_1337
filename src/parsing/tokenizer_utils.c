/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:06 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 16:38:15 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	quote_handler(char *line, int *i, int *words, int *type)
{
	char	quote;

	quote = line[*i];
	while (line[(*i)])
	{
		(*i)++;
		(*words)++;
		if (line[*i] == '$' && quote == '"')
		{
			var_handler(line, i, words, type);
			*type = EXPND_VB;
		}
		if (line[*i] == quote)
		{
			(*i)++;
			(*words)++;
			return (true);
		}
	}
	return (g_xst = 258, quotes_error(quote), false);
}

bool	env_check(char *str, t_data *data)
{
	t_env	*tmp;
	char	*rvalue;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
			return (true);
			tmp = tmp->next;
	}
	return (false);
}

void	var_handler(char *line, int *i, int *words, int *type)
{
	int	*tmp;

	tmp = i;
	while (line[*i] && !((ft_isalnum(line[*i]) || line[*i] == '_')))
	{
		(*i)++;
		(*words)++;
		if (line[*i] == '$')
		{
			(*i)++;
			(*words)++;
			return ;
		}
	}
	i = tmp;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
	{
		(*i)++;
		(*words)++;
	}
}
