/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/20 02:21:14 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//TODO main function will have all our structs assigned into t_data
int main(int ac, char **av, char    **envp)
{
    (void)ac;
    (void)av;
    t_data  data;
    t_ptr   *ptrs = NULL;
    data.cmd = NULL;
    data.ptrs = ptrs;
    data.cmd  = NULL;
   
   data.env = env_list(envp);
    ft_shell(&data, data.env, envp);
    // print_env(env);

    // while (1)
    // {
    //     tmp = &data.cmd;
    //     line = ft_strtrim(readline("Minishell$ "), " ");
        
    // }
}
