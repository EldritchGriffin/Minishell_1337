/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:23:54 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/24 05:07:59 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*check_expanding(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str + 1))
			return (str = ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (str);
}

int	here_doc(t_cmd *delemiter, t_data *data)
{
	int		fd[2];
	char	*str;
	int		her_doc;

	pipe(fd);
	while (1)
	{
		str = readline("> ");
		if (delemiter->type != D_QUOTES || delemiter->type != S_QUOTES)
		{
			if (str && str[0] == '$')
				str = check_expanding(str, data);
		}
		if (!str)
		{
			printf("\b\b  \b\b\n");
			break ;
		}
		if (!ft_strcmp(delemiter->str, str))
			break ;
		str = ft_strjoin(str, "\n");
		write(fd[1], str, ft_strlen(str));
	}
	close(fd[1]);
	return (fd[0]);
}