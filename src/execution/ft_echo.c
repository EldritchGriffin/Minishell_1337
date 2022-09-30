/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:59:54 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/30 09:03:58 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_words(t_exc	*exc, int i)
{
	char	**spltd;
	int		j;

	if (exc->flg[i] == '1')
	{
		j = 0;
		spltd = ft_split(exc->str[i], ' ');
		while (spltd[j])
		{
			ft_putstr_fd(spltd[j], exc->out_file);
			if (spltd[j + 1])
				ft_putstr_fd(" ", exc->out_file);
			j++;
		}
		free_tab(spltd);
	}
	else
		ft_putstr_fd(exc->str[i], exc->out_file);
}

static	int	check_opt(t_exc	*exc, bool	*mode)
{
	int		i;
	int		j;
	t_exc	*tmp;

	i = 0;
	j = 0;
	tmp = exc;
	*mode = false;
	while (exc->str[++i])
	{
		j = 0;
		if (exc->str[i][j++] == '-' && exc->str[i][1] == 'n')
		{
			while (exc->str[i][j] == 'n')
				j++;
			if (!exc->str[i][j])
				*mode = true;
			else
				return (i);
		}
		else
			break ;
	}
	return (i);
}

void	ft_echo(t_exc	*exc)
{
	int		i;
	bool	mode;

	i = check_opt(exc, &mode);
	if (!exc->str[1])
	{
		if (!mode)
			return (ft_putstr_fd("\n", exc->out_file), (void)0);
		else
			return ;
	}
	while (exc->str[i])
	{
		handle_words(exc, i);
		if (exc->str[i + 1])
			ft_putstr_fd(" ", exc->out_file);
		i++;
	}
	if (!mode)
		ft_putstr_fd("\n", exc->out_file);
	g_xst = 0;
}
