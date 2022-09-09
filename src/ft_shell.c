/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/09 02:32:19 by aelyakou         ###   ########.fr       */
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
///-----------this function jut for test------------------------------------

static void   execve_test(char **tab, t_data *data)
{
    int     i;
    int     j;
	char	*cmd;
	char   	*line;
    char    **str;
    char    **path;

    str = get_path(data);
    j = 0;
	cmd = ft_strdup("/"); 
    while (tab[j]) 
    {
        i = 0;
		line = ft_strjoin(cmd, tab[j]);
        while (str[i])
        {
            str[i] = ft_strjoin(str[i], line);
            execve(str[i], &str[i], NULL);
					
            i++;
        }
        j++;
    }
}

void    ft_shell(t_data *data, t_env *env)
{
	char	*line;
	char    *str;
	char 	**tab;
	t_cmd	**tmp;
	int		i;

	while (1)
	{
	 	tmp = &data->cmd;	
		line = readline("Minishell$ ");
		if (line)
		{
			add_history(line);
			str = ft_strtrim(line, " "); // removing space form the end and the start. NOTIC : im gonna change it latterrr
			if (build_token_list(str, data))
			{
				while((*tmp))
				{ 
					join_unspaced(tmp, &((*tmp)->next), &data);
					tmp = &(*tmp)->next;
				}
				tab = parse_args(data); // im still workin on this fucntions (this function is the final part we still need to check other things before we use this fucntion)
				var_expnd(data);
				identify_builtin(data);
				print_cmd(data->cmd);
				 execve_test(tab, data);
				data->cmd = NULL;
			}
		} 
	}
}
