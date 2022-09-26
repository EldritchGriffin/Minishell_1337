/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:59:54 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/25 21:39:23 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static	int	check_opt(t_exc	*exc, bool	*mode)
{
	int i;
	int	j;
	t_exc	*tmp;

	i = 0;
	j = 0;
	tmp = exc;
	*mode = false;
	while (exc->str[++i])
	{
		j = 0;
		if(exc->str[i][j++] == '-' && exc->str[i][1] == 'n')
		{
			while(exc->str[i][j] == 'n')
				j++;
			if(!exc->str[i][j])
				*mode = true;
			else
				return (i);
		}
		else
			break;
	}
	return (i);
}

void	ft_echo(t_exc	*exc)
{
	int	i;
	bool	mode;

	i = check_opt(exc, &mode);
	if(!exc->str[1])
	{
		if(!mode)
			return(ft_putstr_fd("\n", exc->out_file), (void)0);
		else
			return;

	}
	while(exc->str[i])
	{
		ft_putstr_fd(exc->str[i], exc->out_file);
			if(exc->str[i + 1])
				ft_putstr_fd(" ", exc->out_file);
		i++;
	}
	if(!mode)
		ft_putstr_fd("\n", exc->out_file);
}
