/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:36 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/11 06:01:45 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


//TODO main function will have all our structs assigned into t_data
int main(int ac, char **av, char    **envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    t_data  data;
    t_ptr   *ptrs = NULL;
    t_env   *env = NULL;
    data.cmd = NULL;
    data.ptrs = ptrs;
    data.cmd  =NULL;
    env = env_list(envp);
    data.env = env;
    // print_env(env);
     ft_shell(&data, env);
}
