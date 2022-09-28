/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/28 10:16:57 by aelyakou         ###   ########.fr       */
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
		rederection_check(&exc, her_file);
		if (!exc->str[0])
			return ;
		if (!identify_builtin(data, exc))
			return ;
		else
		{
			bin = get_path(exc->str, data);
			exec_cmd(exc, bin, envp);
			free (bin);
		}
	}
	// free_cmd(data);
	// free_exc(data);
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
		var_expnd(data);
		while ((*tmp))
		{
			join_unspaced(tmp, &((*tmp)->next), &data);
			tmp = &(*tmp)->next;
		}
		fill_exclist(data->cmd, data);
		print_exc(data->exc);
		// print_cmd(data->cmd);
		data->pps->p_c = check_pipes(data->exc);
		cmd_call(data->exc, data, envp, her_file);
		// free_cmd(data);
		// free_exc(data);
		// free_env(data);
}
	// initalize_data(&data);
}
