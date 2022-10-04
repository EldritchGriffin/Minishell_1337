/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:41:35 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/04 08:11:22 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	identify_builtin(t_data *data, t_exc	*cmd)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "echo"))
		return (ft_echo(cmd), 0);
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "cd"))
		return (ft_cd(data), 0);
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "pwd"))
		return (ft_pwd(data), 0);
	if (!ft_strcmp(cmd->str[0], "export"))
		return (ft_export(cmd, data), 0);
	if (!ft_strcmp(cmd->str[0], "unset"))
		return (ft_unset(cmd, data), 0);
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "env"))
	{
		if (cmd->str[1])
			return (ft_putstr_fd("env with No arguments\n", STDERR), 0);
		return (print_env(data->env, data), 0);
	}
	if (!ft_strcmp(cmd->str[0], "exit"))
	{
		return (ft_exit(cmd), 0);
	}
	return (1);
}
