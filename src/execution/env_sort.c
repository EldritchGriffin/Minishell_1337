#include "../../headers/minishell.h"

// workk not doneee yet-----------------------------------------------------------------

size_t envtab_len(char **env)
{
    size_t     i;

    i = 0;
    while (env[i])
        i++;
    return(i);
}

int    env_len(t_env *env)
{
    t_env *tmp;
    int i;

    i = 0;
    tmp = env;
    while(tmp)
    {   
        i++;
        tmp = tmp->next;
    }
    return(i);
}

char    *env_to_str(t_env *env, t_data *data)
{
    t_env   *tmp;
    char    *str;
    int size;
    int i;

    tmp = env;
    i = 0;
    size = env_len(env);
    str = ft_malloc(size, &data->ptrs);
    if (!str)
        rteurn(NULL);
    while(tmp)
    {
        str[i] = tmp->value;
        tmp = tmp->next;
        i++;
        if (tmp->next->next !=NULL);
    }



}
void    sorted_env(t_env *env)
{
    char **str;
    char  *str_to_env;
    int    i;





}




