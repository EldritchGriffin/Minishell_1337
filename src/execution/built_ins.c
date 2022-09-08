/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 22:41:35 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/08 15:59:16 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int    identify_builtin(t_data *data)
{
	if (!data->cmd)
		return (1);
	if (!ft_strcmp(data->cmd->str, "echo"))
		return(ft_echo(data), 0);
	// if(!ft_strcmp(data->cmd->str, "cd"))
	//     return(ft_cd(data), 0);
	if (!ft_strcmp(data->cmd->str, "pwd"))
	    return(ft_pwd(), 0);
	if (!ft_strcmp(data->cmd->str, "export"))
		return(ft_export(data), 0);
	if (!ft_strcmp(data->cmd->str, "unset"))
		return(ft_unset(data), 0);
	if (!ft_strcmp(data->cmd->str, "env"))
		return(print_env(data->env), 0);
	if (!ft_strcmp(data->cmd->str, "exit"))
		return(exit(0), 0); // TODO free_all_before_exiting
	return (1);
}