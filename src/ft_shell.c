/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/12 09:47:31 by zrabhi           ###   ########.fr       */
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

	// /i = 0;
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


void	cmd_call(t_exc *exc, t_data *data)
{
	int		i;
	char	*bin;
	
	i = -1;
	if (!identify_builtin(data))
		return ;
	while (exc)
	{
		bin = get_path(exc->str, data);
		exec_cmd(exc->str, bin);
		exc = exc->next;
		free(bin);
	}
}

void    ft_shell(t_data *data, t_env *env)
{
	int		i;
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
				while((*tmp))
				{ 
					join_unspaced(tmp, &((*tmp)->next), &data);
					tmp = &(*tmp)->next;
				}
				tab = parse_args(data);
				build_exc_list(tab, data);
				cmd_call(data->exc, data);
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
