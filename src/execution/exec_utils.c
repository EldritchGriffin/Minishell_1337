/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 17:58:59 by aelyakou          #+#    #+#             */
/*   Updated: 2022/09/29 22:14:06 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int check_identifier(char	*str)
{
	int i;

	i = 0;
	if(str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	while(str[++i])
	{
		if(str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
	}
	return (0);
}

void	ft_dup(int *in_save, int *out_save)
{
	*in_save = dup(STDIN_FILENO);
	*out_save = dup(STDOUT_FILENO);
}

void	ft_cat(char **bin, char *path_split, char *cmd)
{
	char *tmp;
	
	tmp = *bin;
	*bin = ft_strjoin(*bin, path_split);
	free(tmp);
	tmp = *bin;
	*bin = ft_strjoin(*bin, "/");
	free(tmp);
	tmp = *bin;
	*bin = ft_strjoin(*bin, cmd);
	free(tmp);
}

void	ft_dup2(int *in_file, int *out_file, int fd0, int fd1)
{
	dup2(*out_file, fd1);
	dup2(*in_file, fd0);
}
	