/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/05 01:50:00 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Testing purposes again...
void    print_cmd(t_cmd *cmd)
{
	while(cmd)
	{
		printf  ("string is [%s] ------ token value is [%d] ------ operator id [%d]\n",cmd->str, cmd->type, cmd->opr);
		cmd = cmd->next;
	}
}

void print_exc(t_exc *exc)
{
	int i;

	while (exc)
	{
		i = -1;
		while(exc->str[++i])
			printf  ("exc ========= is[%s]\n", exc->str[i]);
		printf  ("MOVING  to the next\n");
		exc = exc->next;
	}	
}


void	cmd_call(t_exc *exc, t_data *data, char **envp, int her_file)
{
	int		i;
	int		check;
	char	*bin;

	i = 0;
	check = 2;
	if (data->pps->p_c)
		return (exec_pipes(exc, data, her_file, envp), \
			free_cmd(data), free_exc(data), (void)0);
	else
	{
		i = rederection_check(&exc, her_file);
		if (!exc->str[0] || exc->in_file == -1 || i == 2
			|| !identify_builtin(data, exc))
			return (free_cmd(data), free_exc(data), (void)0);
		else
		{
			bin = get_path(exc->str, data, &check);
			exec_cmd(exc, bin, envp);
			if (!check)
				free(bin);
		}
	}
	return (free_cmd(data), free_exc(data), (void)0);
}

static	void	initalize_data(t_data **data)
{
	(*data)->exc = NULL;
	(*data)->cmd = NULL;
}

void	ft_shell(char *line, t_data *data, t_env *env, char **envp)
{
	t_cmd	**tmp;
	int		her_file;

	her_file = 0;
	tmp = &data->cmd;
	if (build_token_list(line, data, &her_file))
	{
		free(line);
		var_expnd(data);
		while ((*tmp))
		{
			join_unspaced(tmp, &((*tmp)->next), &data);
			tmp = &(*tmp)->next;
		}
		fill_exclist(data->cmd, data);
		data->pps->p_c = check_pipes(data->exc);
		cmd_call(data->exc, data, envp, her_file);
	}
	else if (line && line[0])
		free(line);
}
