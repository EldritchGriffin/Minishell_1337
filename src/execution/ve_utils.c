/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ve_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:47:52 by aelyakou          #+#    #+#             */
/*   Updated: 2022/10/05 21:51:46 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_ev(t_data *data, char *str)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("\0");
}

char	*get_path(char **cmd, t_data *data, int *check)
{
	char	*path;
	char	*bin;
	char	**path_split;
	int		i;

	path = ft_strdup(get_ev(data, "PATH"));
	if (!*path)
		return (free(path), cmd[0]);
	if ((cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2) == 0))
		return (free(path), *check = 1, cmd[0]);
	path_split = ft_split(path, ':');
	free (path);
	i = -1;
	while (path_split[++i])
	{
		bin = ft_calloc(sizeof(char), (ft_strlen(path_split[i]) \
			+ ft_strlen(cmd[0])) + 2);
		if (!bin)
			return (NULL);
		ft_cat(&bin, path_split[i], cmd[0]);
		if (!access(bin, F_OK | X_OK | R_OK))
			return (free_tab(path_split), *check = 0, bin);
		free(bin);
	}
	return (free_tab(path_split), cmd[0]);
}
