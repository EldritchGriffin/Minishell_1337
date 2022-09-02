#include "../../headers/minishell.h"

// workk not doneee yet-----------------------------------------------------------------

static size_t envtab_len(char **env)
{
    size_t     i;

    i = 0;
    while (env[i])
        i++;
    return(i);
}

static int    env_len(t_env *env)
{
    t_env *tmp;
    int i;

    i = 0;
    tmp = env;
    while(tmp)
    {   
        i += ft_strlen(tmp->key);
        i += ft_strlen(tmp->value);
        i++;
        tmp = tmp->next;
    }
    return (i);
}

static char    *env_to_str(t_env *env, t_data *data)
{
    t_env   *tmp;
    char    *str;
    int size;
    int i;
    int j;

    tmp = env;
    i = 0;
    j = 0;
    size = env_len(env);
    str = malloc(size + 1);
    if (!str)
        return(NULL);
    while(tmp)
    {
        while (tmp->key[j])
        {
            str[i] = tmp->key[j];
            i++;
            j++;
        }
        
        j = 0;
        while (1)
        {
            str[i] = tmp->value[j];
            i++;
            j++;
            if (!tmp->value[j + 1])
                str[i] = '\n';
        }
        // if (tmp->next != NULL)
            str[i] = '\n';
        j = 0;
        tmp = tmp->next;
    }
    str[i] = '\0';
    return(str);
}

void    sorted_env(t_env *env, t_data *data)
{
    // char **str;
    char  *str_to_env;
    // int    i;

    str_to_env = env_to_str(env, data);
    printf("str ==   %s\n", str_to_env);
}




