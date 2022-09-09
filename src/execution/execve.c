/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:53:22 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/09 17:20:03 by zrabhi           ###   ########.fr       */
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

    path = ft_strdup(getenv("PATH"));
    if (!path)
        path = ft_strdup("/Users/zrabhi/goinfre/homebrew/bin:/Users/zrabhi/goinfre/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/zrabhi/goinfre/.brew/bin");
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
        strcat(bin, path_split[i]);
        strcat(bin , "/");
        strcat(bin, cmd[0]);
        if (!access(bin, F_OK | X_OK | R_OK))
                break ;
    }
    return (bin);
}
void   exec_cmd(char **cmd, char *bin)
{
    pid_t pid = 0;
    int     status = 0;
    
    
    pid = fork();
    if (pid == -1)
        perror("fork");
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        printf("status === %d\n", status);
        kill(pid, SIGINT);
    }
    else if (pid == 0)
    {
            if (execve(bin, cmd, NULL) == -1)
                    // perror("Minishell$ ");
            exit (EXIT_SUCCESS);
    }
    // waitpid(pid, &status, 0);
    // kill(pid, SIGINT);
}
