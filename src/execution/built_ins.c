/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:41:35 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/12 20:01:17 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int    identify_builtin(t_data *data)
{
	if (!data->cmd)
		return (1);
	// if (!ft_strcmp(data->cmd->str, "echo") || !ft_strcmp(data->cmd->str, "ECHO"))
	// 	return(ft_echo(data), 0);
	// if(!ft_strcmp(data->cmd->str, "cd"))
	//     return(ft_cd(data), 0);
	if (!ft_strcmp(data->cmd->str, "pwd") || !ft_strcmp(data->cmd->str, "PWD"))
	    return(ft_pwd(), 0);
	if (!ft_strcmp(data->cmd->str, "export"))
		return(ft_export(data), 0);
	if (!ft_strcmp(data->cmd->str, "unset"))
		return(ft_unset(data), 0);
	if (!ft_strcmp(data->cmd->str, "env") || !ft_strcmp(data->cmd->str, "ENV"))
		return(print_env(data->env), 0);
	if (!ft_strcmp(data->cmd->str, "exit"))
		return(exit(0), 0); // TODO free_all_before_exiting
	return (1);
}