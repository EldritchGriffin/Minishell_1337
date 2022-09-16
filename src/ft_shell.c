/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/16 17:15:55 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//Testing purposes again...
static  void    print_cmd(t_cmd *cmd)
{
    while(cmd)
    {
        printf("string is [%s] ------ token value is [%d] ------ operator id [%d]\n",cmd->str, cmd->type, cmd->opr);
        cmd = cmd->next;
    }
}

static void print_exc(t_exc *exc)
{
	int i;

	while (exc)
	{
		i = -1;
		while(exc->str[++i])
			printf("exc ========= is[%s]\n", exc->str[i]);
		printf("node-----> IN_  %d   OUT_   %d\n", exc->in_file, exc->out_file);
		printf("MOVING  to the next\n");
		exc = exc->next;
	}	
}
///-----------this function jut for test------------------------------------


void	cmd_call(t_exc *exc, t_data *data)
{
	int		i;
	int j = -1;
	char	*bin;
	
	i = -1;
	if (!identify_builtin(data))
		return ;
	while (exc)
	{
		bin = get_path(exc->str, data);
		printf("bin == %s\n", bin);
		exec_cmd(exc->str, bin);
		exc = exc->next;
		free(bin);
	}
}

void    ft_shell(t_data *data, t_env *env)
{
	int		her_file;
	t_cmd	**tmp;
	char	*line;
	char    *str;
	char 	**tab;

	while (1)
	{
	 	tmp = &data->cmd;	
		line = readline("Minishell$ ");
		if (line)
		{
			add_history(line);
			str = ft_strtrim(line, " ");
			if (build_token_list(str, data))
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
					print_exc(data->exc);
					cmd_call(data->exc, data);
				}
				data->exc = NULL;
				data->cmd = NULL;
			}
			else {
				data->exc = NULL;
				data->cmd = NULL;
			}
		} 
	}
}
