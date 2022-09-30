/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 04:06:41 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/29 23:33:38 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
# define  static const char *RDS[5] = {">>", "<<", "<", ">", NULL};

static int	exctab_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
char 	*ft_join_exc(char *str, char *cmd)
{
	char *tmp;
	char *lrt;

	lrt = ft_strjoin(str, cmd);
	free(str);
	tmp = lrt;
	lrt = ft_strjoin(lrt, ":");
	free(tmp);
	return (lrt);
}

//FIXME problem with the assigned array, you will probably need to use a pointer instead;
char	*get_redirection(t_exc **exc, int her_file, int *result)
{
	int		type[] = {APPEND, HERDOC, I_REDIRECTION, O_REDIRECTION};
	int		i;
	int		j;
	int		check;
	char	*str;
	char	*tmp;

	check = 0;
	i = -1;
	str = ft_strdup("");
	while ((*exc)->str[++i])
	{
		j = -1;
		check = 0;
		while (RDS[++j])
		{
			if (!ft_strcmp((*exc)->str[i], RDS[j]))
			{
				check = 1;
				if (!(*exc)->str[i + 1])
				{
					check = 0;
					break ;
				}
				i++;
				if (!ft_open(&(*exc)->out_file, &(*exc)->in_file, \
				j, (*exc)->str[i]))
				if (her_file)
					(*exc)->in_file = her_file;
				*result = 1;
			}
		}
		if (!check)
			str = ft_join_exc(str, (*exc)->str[i]);
	}
	return (str);
}

int	rederection_check(t_exc **exc, int her_file)
{
	t_exc	*tmp;
	int		i;
	int		result;
	char	*str;

	result = 0;
	i = -1;
	tmp = *exc;
	str = get_redirection(&tmp, her_file, &result);
	if (result)
	{
		free_tab((*exc)->str);
		(*exc)->str = ft_split(str, ':');
	}
	free(str);
	return (result);
}
