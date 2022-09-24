/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/24 04:22:49 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Testing purposes again...
void    print_cmd(t_cmd *cmd)
{
    while(cmd)
    {
        printf("string is [%s] ------ token value is [%d] ------ operator id [%d]\n",cmd->str, cmd->type, cmd->opr);
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
			printf("exc ========= is[%s]\n", exc->str[i]);
		printf("MOVING  to the next\n");
		exc = exc->next;
	}	
}

///-----------this function jut for test------------------------------------

void	cmd_call(t_exc *exc, t_data *data, char **envp, int her_file)
{
	int		i;
	char	*bin;

	i = 0;
	if (data->pps->p_c)
	{
		exec_pipes(exc, data, her_file, envp);
		return ;
	}
	else
	{
		bin = get_path(exc->str, data);
		rederection_check(&exc, her_file);
		if (!identify_builtin(data))
			return ;
		if (!exc->str[0])
			return ;
		else
			exec_cmd(exc, bin, envp);
		free (bin);
	}
}

static	void	initalize_data(t_data **data)
{
	(*data)->exc = NULL;
	(*data)->cmd = NULL;
}

void	ft_shell(char *line, t_data *data, t_env *env, char **envp)
{
	t_cmd	**tmp;
	char	**tab;
	int		her_file;

	her_file = 0;
	tmp = &data->cmd;
	if (build_token_list(line, data, &her_file))
	{
		while ((*tmp))
		{
			join_unspaced(tmp, &((*tmp)->next), &data);
			tmp = &(*tmp)->next;
		}
		var_expnd(data);
		tab = parse_args(data);
		if (tab)
		{	
			build_exc_list(tab, data);
			data->pps->p_c = check_pipes(data->exc);
			cmd_call(data->exc, data, envp, her_file);
		}
	}
	initalize_data(&data);
}
