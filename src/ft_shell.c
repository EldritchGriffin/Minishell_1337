/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:32 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/09 05:55:15 by zrabhi           ###   ########.fr       */
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
            if (execve(str[i], &str[i], NULL) == -1)
					return (perror("Minishell$ : "), (void)0);
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
				build_exc_list(tab, data);
				identify_builtin(data);
				print_cmd(data->cmd);
				print_exc(data->exc);
				// execve_test(tab, data);
				data->cmd = NULL;
			}
		} 
	}
}
