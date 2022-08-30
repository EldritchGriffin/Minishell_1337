#include "../../headers/minishell.h"

static  t_cmd   *new_node(char  *str, t_tokens type, t_data *data)
{
    t_cmd   *new_node;

    new_node =  ft_malloc(sizeof(t_cmd), &data->ptrs);
    new_node->str = str;
    new_node->type = type;
    new_node->next = NULL;
    return (new_node);
}

static  void    add_back(t_cmd  **cmd, t_cmd    *new_node)
{
    t_cmd   *tmp;
    if(!cmd || !new_node)
        return ;
    if(!*cmd)
    {
        *cmd = new_node;
        return ;
    }
    tmp = *cmd;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    return ;
}

void    cmd_list(char *str, t_tokens token, t_data *data)
{
    add_back(&data->cmd, new_node(str, token, data));
}

