/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:41:35 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/02 01:23:57 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	identify_builtin(t_data *data, t_exc	*cmd)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd->str[0], "echo") || !ft_strcmp(cmd->str[0], "ECHO"))
		return (ft_echo(cmd), 0);
	if (!ft_strcmp(cmd->str[0], "cd"))
		return (ft_cd(data), 0);
	if (!ft_strcmp(cmd->str[0], "pwd") || !ft_strcmp(cmd->str[0], "PWD"))
		return (ft_pwd(data), 0);
	if (!ft_strcmp(cmd->str[0], "export"))
		return (ft_export(cmd, data), 0);
	if (!ft_strcmp(cmd->str[0], "unset"))
		return (ft_unset(cmd, data), 0);
	if (!ft_strcmp(cmd->str[0], "env") || !ft_strcmp(cmd->str[0], "ENV"))
		return (print_env(data->env, data), 0);
	if (!ft_strcmp(cmd->str[0], "exit"))
		return (exit(0), 0);
	return (1);
}
