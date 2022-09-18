/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:53:22 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/18 23:30:15 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char *get_ev(t_data *data, char *str)
{
    t_env *tmp;
    
    tmp = data->env;
    while (tmp)
    {
        if (ft_strcmp(str, tmp->key) == 0)
            return (tmp->value);

    tmp = tmp->next;
    }
    return (NULL);
}


char   *get_path(char **cmd, t_data *data)
{
    char    *path;
    char    *bin;
    char    **path_split;
    int     i;
    int     path_len;

    path = ft_strdup(get_ev(data, "PATH"));
    if (!path)
         return (NULL); 
    if (cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2 ) == 0)
                return (cmd[0]);
    path_split = ft_split(path, ':');
    free (path);
    path = NULL;
    i = -1;
    while (path_split[++i])
    {
        path_len = ft_strlen(path_split[i]);
        bin = ft_calloc(sizeof(char), (path_len + ft_strlen(cmd[0])) + 2);
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
void   exec_cmd(t_exc *exc, char *bin, int is_redi, char **envp)
{
    pid_t   pid = 0;
    int     status = 0;
    
    pid = fork();
    if (pid == 0)
    {
        if (is_redi)
        {
            dup2(exc->out_file, STDOUT_FILENO);
            close(exc->out_file);
        }
        status =  execve(bin, &exc->str[0], envp);
        if (status == -1)
        {   
            printf("Minishell : %s: command not found\n", exc->str[0]);
            waitpid(pid, &status, 0);
            exit(EXIT_FAILURE);
        }
    }
    waitpid(pid, &status, 0);
}