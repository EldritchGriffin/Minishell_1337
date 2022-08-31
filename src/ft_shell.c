/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/08/31 17:48:28 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../LIBFT/libft.h"

//Testing purposes again...
static  void    print_cmd(t_cmd *cmd)
{
    while(cmd)
    {
        printf("string is [%s] ------ token value is [%d]\n",cmd->str, cmd->type);
		// if(cmd->prev)
			//printf("string prev is [%s] ------ token value is [%d]\n",cmd->prev->str, cmd->prev->type);
        cmd = cmd->next;
    }
}

void    ft_shell(t_data *data, t_env *env)
{
	char	*line;
	t_cmd	**tmp;

	while (1)
	{
	tmp = &data->cmd;	
		line = readline("Minishell$ ");
		add_history(line);
		build_token_list(line, data);
		while((*tmp))
		{
			printf("im here\n");
			join_unspaced(tmp, &(*tmp)->next, data);
			tmp = &(*tmp)->next;
		}
		print_cmd(data->cmd);
		identify_builtin(data);
		//destroy(&data->ptrs);   // it cause sgmentation fault,
		data->cmd = NULL; 
	}
}
