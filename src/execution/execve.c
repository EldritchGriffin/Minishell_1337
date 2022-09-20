/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:53:22 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/20 01:21:09 by zrabhi           ###   ########.fr       */
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


static void ft_dup(int *in_save, int *out_save)
{
    *in_save = dup(STDIN_FILENO);
    *out_save = dup(STDOUT_FILENO);   
}

static void ft_cat(char **bin, char *path_split, char *cmd)
{
    ft_strcat(*bin, path_split);
    ft_strcat(*bin, "/");
    ft_strcat(*bin, cmd);
}

static void ft_dup2(int *in_file, int *out_file, int fd0, int fd1)
{
    dup2(*out_file, fd1);
    dup2(*in_file, fd0);
}

char   *get_path(char **cmd, t_data *data)
{
    char    *path;
    char    *bin;
    char    **path_split;
    int     i;

    path = ft_strdup(get_ev(data, "PATH"));
    if (!path)
         return (NULL); 
    if ((cmd[0][0] == '/' || ft_strncmp(cmd[0], "./", 2 ) == 0)
                && !access(bin, F_OK | X_OK | R_OK))
                return (cmd[0]);
    path_split = ft_split(path, ':');
    free (path);
    i = -1;
    while (path_split[++i])
    {
        bin = ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + ft_strlen(cmd[0])) + 2);
        if (!bin)
            return (NULL);
        ft_cat(&bin, path_split[i], cmd[0]);
        if (!access(bin, F_OK | X_OK | R_OK))
                 break ;
    }
    return (bin);
}

void   exec_cmd(t_exc *exc, char *bin, int is_redi, char **envp)
{
    pid_t   pid = 0;
    int     status = 0;
    int     in_save;
    int     out_save;

    ft_dup(&in_save, &out_save);
    ft_dup2(&exc->in_file, &exc->out_file,\
             STDIN_FILENO, STDOUT_FILENO);
    pid = 0;  
    pid = fork();
    if (pid == 0)
    {
        status =  execve(bin, &exc->str[0], envp);
        if (status == -1)
        {   
            printf("Minishell : %s: command not found\n", exc->str[0]);
            waitpid(pid, &status, 0);
            exit(EXIT_FAILURE);
        }
    }
    waitpid(pid, &status, 0);
    if (exc->in_file != 0)
         close(exc->in_file);
    if (exc->out_file != 1)
        close(exc->out_file);
    dup2(in_save, STDIN);
    dup2(out_save, STDOUT);
}