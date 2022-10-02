/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:16:17 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/02 16:44:48 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit(t_exc	*cmd)
{
	int	i;
	int	xst;

	i = 0;
	if (cmd->str[1])
	{
		if (cmd->str[2])
			return (g_xst = 1, ft_putstr_fd("exit\ntoo many arguments\n",
					STDERR));
		while (cmd->str[1][i])
		{
			if (!ft_isdigit(cmd->str[1][i]))
			{
				ft_putstr_fd("Numeric argument required\n", STDERR);
				exit (255);
			}
			else
			{
				xst = ft_atoi(cmd->str[1]);
				exit((char)xst);
			}
		}
		i++;
	}
	exit(0);
}
