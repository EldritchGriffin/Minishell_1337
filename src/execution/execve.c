#include "../../headers/minishell.h"


char **get_path(t_data *data)
{
    t_env   *tmp;
    char    **str;
    
    tmp = data->env;
    str = NULL;
    while (tmp)
    {
        if (ft_strcmp("PATH", tmp->key) == 0)
            str = ft_split(tmp->value, ':');
    tmp = tmp->next;
    }
    return(str);
}