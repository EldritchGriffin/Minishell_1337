/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:53:57 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/03 05:22:33 by zrabhi           ###   ########.fr       */
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
					|| hdc->next->next->type == S_QUOTES
					|| hdc->next->next->type == VARIABLE
					||hdc->next->next->type == EXPND_VB))
				*her_file = here_doc(hdc->next->next, data);
		}
		hdc = hdc->next;
	}
}
