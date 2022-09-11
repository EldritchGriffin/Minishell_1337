/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:53:22 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/11 05:33:34 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char   *get_path(char **cmd)
{
    char    *path;
    char    *bin;
    char    **path_split;
    int     i;
    int     path_len;
    int     cmd_len;
    int     j;

    path = ft_strdup(getenv("PATH"));
    if (!path)
        return (NULL);
    if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2 ) == 0)
            return (cmd[0]);
    path_split = ft_split(path, ':');
    free (path);
    i = -1; 
    cmd_len = ft_strlen(cmd[0]);
    while (path_split[++i])
    {
        path_len = ft_strlen(path_split[i]);
        bin = ft_calloc(sizeof(char), (path_len + cmd_len) + 2);
        if (!bin)
            return (NULL);
        ft_strcat(bin, path_split[i]);
        ft_strcat(bin , "/");
        ft_strcat(bin, cmd[0]);
        if (!access(bin, F_OK | X_OK | R_OK))
                 break ;
    }
    return (bin);
}
void   exec_cmd(char **cmd, char *bin)
{
    pid_t   pid = 0;
    int     status = 0;
    
    
    pid = fork();
    if (pid == -1)
        perror("fork");
    if(pid == 0)
    {
        status = execve(bin, cmd, NULL);
        if(status == -1)
        {
            waitpid(pid, &status, 0);
            exit(EXIT_FAILURE);
        }

    }
    waitpid(pid, &status, 0);
}
