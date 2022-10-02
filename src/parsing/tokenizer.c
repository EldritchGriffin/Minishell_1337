/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:14 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/02 00:31:14 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	ft_break(int a, int b)
{
	if (b == VARIABLE)
		return (true);
	else if (b == S_QUOTES)
		return (true);
	else if (b == D_QUOTES)
		return (true);
	if (a != b)
		return (true);
	else if (a == b)
		return (false);
	else if (b == SPC)
		return (true);
	return (false);
}

static int	ft_creat_list(int old_type, t_data *data, int operator, char *line)
{
	if (old_type == SPC)
		return (cmd_list(ft_strdup(" "), old_type, 0, data), true);
	if (old_type == WORD)
		return (cmd_list(line, old_type, 0, data), true);
	else
		return (cmd_list(line, old_type, operator, data), true);
	return (true);
}

static void	initalize_tokens(t_data **data, char *line, int *i, int *check)
{
	(*data)->tokens->operator = false;
	(*data)->tokens->tmp_type = get_token_type(line[*i], \
	&(*data)->tokens->operator);
	(*data)->tokens->old_type = (*data)->tokens->tmp_type;
	*check = (*i);
}

int	get_token(char *line, int *i, int words, t_data	*data)
{
	int		check;
	char	*str;

	initalize_tokens(&data, line, i, &check);
	while (1)
	{
		data->tokens->tmp_type = get_token_type(line[*i], \
		&data->tokens->operator);
		words++;
		if (ft_break(data->tokens->old_type, data->tokens->tmp_type) \
		|| !line[*i])
			break ;
		(*i)++;
	}
	data->tokens->old_type = redirection_handler(line[check], line[check + 1], \
			data->tokens->old_type, &data->tokens->operator);
	if (!check_old_type(line, i, &words, &data->tokens->old_type))
		return (0);
	str = ft_substr(line, check, words);
	if (str[0] == ' ')
		free(str);
	ft_creat_list(data->tokens->old_type, data, data->tokens->operator, str);
	if (data->tokens->operator == true && data->tokens->tmp_type != SPC)
		cmd_list(ft_strdup(" "), SPC, 0, data);
	return (1);
}
