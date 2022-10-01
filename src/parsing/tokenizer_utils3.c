/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 08:38:22 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/01 08:40:23 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	get_token_type(char line, bool *operator)
{
	if (line == '|')
		return ((*operator = true), PIPE);
	else if (line == '\'')
		return (S_QUOTES);
	else if (line == '>')
		return ((*operator = true), O_REDIRECTION);
	else if (line == '<')
		return ((*operator = true), I_REDIRECTION);
	else if (line == '\"')
		return (D_QUOTES);
	else if (line == '$')
		return (VARIABLE);
	else if (line == ' ' || line == '\t')
		return (SPC);
	return (WORD);
}

int	build_token_list(char *line, t_data *data, int *her_file)
{
	int		i;
	int		words;
	t_cmd	*tmp;
	t_cmd	*hdc;

	i = -1;
	while (line[++i])
	{
		words = -1;
		if (!get_token(line, &i, words, data))
			return (0);
		i--;
	}
	if (!rm_quotes(&data))
		return (free_cmd(data), 0);
	if (!check_operatrs_first(data))
		return (free_cmd(data), 0);
	herdoc_handler(data, her_file);
	if (!check_operators_sec(data))
		return (free_cmd(data), 0);
	return (1);
}