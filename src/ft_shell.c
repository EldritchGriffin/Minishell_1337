/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/01 05:34:05 by zrabhi           ###   ########.fr       */
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
// static void       join_unspaced1(t_cmd **cmd)
// {
//     char  *str;
//     char  *join;
//     int  count;
//     t_cmd *tmp;
//     t_cmd *s_node;
//     int     i;

//     count = 0;
//     tmp = (*cmd);
// 	s_node = (*cmd);
//     while(tmp)
//     {
//         i = search_spc_node(&s_node);
// 		printf("i : %d\n", i);
//         while (count < i)
//         {
//             str = ft_strjoin(tmp->str, tmp->next->str);
//             // tmp = tmp->next;
// 			count++;
//         }
// 		tmp = tmp->next;
//     }
//     printf("lineee : %s         \n", str);
// 	if (s_node)
// 		join_unspaced1(tmp);
// }

void    ft_shell(t_data *data, t_env *env)
{
	char	*line;
	t_cmd	**tmp;
	t_cmd 	*tmp1;

	while (1)
	{
	tmp = &data->cmd;	
		line = readline("Minishell$ ");
		add_history(line);
		build_token_list(line, data);
		// while((*tmp))
		// { 
		// 	tmp1 = (*tmp)->next;
		// 	join_unspaced1(tmp, &tmp1, data);
		// 	tmp = &(*tmp)->next;
		// }
		join_unspaced1(tmp, &((*tmp)->next), &data);
		// print_cmd(data->cmd);// change the address here
		//identify_builtin(data);
		//destroy(&data->ptrs);   // it cause sgmentation fault,
		data->cmd = NULL; 
	}
}
