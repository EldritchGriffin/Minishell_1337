/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/03 06:25:40 by zrabhi           ###   ########.fr       */
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
	char    *str;
	t_cmd	**tmp;
	t_cmd 	*tmp1;

	while (1)
	{
	 tmp = &data->cmd;	
		line = readline("Minishell$ ");
		if(line)
		{
			add_history(line);
			str = ft_strtrim(line, " "); // removing space form the end and the start. NOTIC: im gonna change it latterrr
			build_token_list(str, data);
			while((*tmp))
			{ 
				join_unspaced(tmp, &((*tmp)->next), &data);
				tmp = &(*tmp)->next;
			}
			print_cmd(data->cmd);// change the address here
			identify_builtin(data);
			data->cmd = NULL;
		} 
	}
}
