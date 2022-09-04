/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/04 04:33:22 by zrabhi           ###   ########.fr       */
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
        cmd = cmd->next;
    }
}

void    ft_shell(t_data *data, t_env *env)
{
	char	*line;
	char    *str; // im gonna delete it later
	char 	**tab;
	t_cmd	**tmp;
	int 	i;

	while (1)
	{
	 	tmp = &data->cmd;	
		line = readline("Minishell$ ");
		if (line)
		{
			add_history(line);
			str = ft_strtrim(line, " "); // removing space form the end and the start. NOTIC: im gonna change it latterrr
			build_token_list(str, data);
			while((*tmp))
			{ 
				join_unspaced(tmp, &((*tmp)->next), &data);
				tmp = &(*tmp)->next;
			}
			tab = parse_args(data); // im still workin on this fucntions (this function is the final part we still need to check other things before we use this fucntion)
			i = 0;
			while(tab[i])
			{
				ft_putstr_fd("line :  ", 1);
				ft_putendl_fd(tab[i], 1);
				i++;
			}
			identify_builtin(data);
			print_cmd(data->cmd);// change the address her
			data->cmd = NULL;
		} 
	}
}
