/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:41:35 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/24 00:04:20 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	identify_builtin(t_data *data)
{
	char	*str;

	if (!data->cmd)
		return (1);
	str = ft_strdup(data->cmd->str);
	if (!ft_strcmp(str, "echo"))
		return (ft_echo(data), 0);
	if (!ft_strcmp(str, "cd"))
		return (ft_cd(data), 0);
	if (!ft_strcmp(str, "pwd"))
		return (ft_pwd(data), 0);
	if (!ft_strcmp(str, "export"))
		return (ft_export(data), 0);
	if (!ft_strcmp(str, "unset"))
		return (ft_unset(data), 0);
	if (!ft_strcmp(str, "env"))
		return (print_env(data->env, data), 0);
	if (!ft_strcmp(str, "exit"))
		return (exit(0), 0);
	return (1);
}