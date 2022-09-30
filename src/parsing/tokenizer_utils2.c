/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:53:57 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/30 09:22:41 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	get_quote(char line)
{
	if (line == '"')
		return ('"');
	return ('\'');
}

int	redirection_handler(char a, char b, int old_type, bool *operator)
{
	if (a == '>' && b == '>')
		return ((*operator = true), APPEND);
	else if (a == '<' && b == '<')
		return ((*operator = true), HERDOC);
	else
		return (old_type);
}

void	t_space_skip(char **line, int *i)
{
	while ((*line[*i] == ' ' || *line[*i] == '\t' || *line[*i] == '\r'
			|| *line[*i] == '\v'))
		(*i)++;
}

bool	rm_quotes(t_data **data)
{
	t_cmd	*cmd;
	char	*tmp;

	cmd = (*data)->cmd;
	if (!cmd)
		return (false);
	while (cmd)
	{
		if (cmd->type == S_QUOTES || cmd->type == D_QUOTES
			|| cmd->type == EXPND_VB)
		{
			tmp = cmd->str;
			cmd->str = trim_quote(cmd->str);
		}
		cmd = cmd->next;
	}
	return (true);
}

void	herdoc_handler(t_data *data, int *her_file)
{
	t_cmd	*hdc;

	hdc = data->cmd;
	while (hdc)
	{
		if (hdc->type == HERDOC)
		{
			if (!hdc->next->opr && hdc->next->type == SPC
				&& (hdc->next->next->type == WORD
					|| hdc->next->next->type == D_QUOTES
					|| hdc->next->next->type == S_QUOTES))
				*her_file = here_doc(hdc->next->next, data);
		}
		hdc = hdc->next;
	}
}
