/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/18 23:53:11 by zrabhi           ###   ########.fr       */
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


void	cmd_call(t_exc *exc, t_data *data, char **envp, int her_file)
{
	int		i;
	int 	j;
	char	*bin;
	
	i = 0;
	if (!identify_builtin(data))
		return ;
	while (exc)
	{
		bin = get_path(exc->str, data);
		j = rederection_check(&exc, her_file);
		exec_cmd(exc, bin, j, envp);
		exc = exc->next;
		free(bin);
	}
}

void    ft_shell(t_data *data, t_env *env, char **envp)
{
	int		her_file;
	t_cmd	**tmp;
	char	*line;
	char 	**tab;

	her_file = 0;
	while (1)
	{
	 	tmp = &data->cmd;	
		line = ft_strtrim(readline("Minishell$ "), " ");
		if (line)
		{
			add_history(line);
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
					cmd_call(data->exc, data, envp, her_file);
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
