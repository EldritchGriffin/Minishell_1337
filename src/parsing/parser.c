/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:53:30 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/01 05:33:58 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char *trim_quote(char *str)
{
    char *lstr;
    char rtr[2];
    
    if(!str)
        return (NULL);
    rtr[0] = get_quote(str[0]);
    rtr[1] ='\0'; 
    lstr = ft_strtrim(str, rtr);
    if(!lstr)
       return (NULL);
    return (lstr);
}


static void replace_nodes(t_cmd **node, t_cmd **node_next, t_cmd **new_node)
{
      t_cmd *tmp1;
      t_cmd *tmp2;

      tmp1 = (*node);
      tmp2 = (*node_next);

      if (tmp1->prev)
    {
     printf("%s\n", tmp1->prev->str);   
           tmp1->prev->next = (*new_node);
    }
      (*new_node)->prev = tmp1->prev;
      if (tmp2->next)
          tmp2->next->prev = (*new_node);
   (*new_node)->next = tmp2->next;
    free(tmp1);
    free(tmp2);
}

void       join_unspaced1(t_cmd **node, t_cmd **node_next, t_data **data)
{
     char    *str1;
    char    *str2;
    char    *join;
    t_cmd   *new_node;
 
    if(!*node || !*node_next || (*node_next)->type == SPC || (*node)->type == SPC)
        return ;
    if (check_one(*node, *node_next))
    {
        printf("in fucntion\n");
        if ((*node)->str[0] == '"' || (*node)->str[0] == '\'')
        str1 = trim_quote((*node)->str);
        else
        str1 = (*node)->str;
        if ((*node_next)->str[0] == '"' || (*node_next)->str[0] == '\'')
        str2 = trim_quote((*node_next)->str);
        else
        str2 = (*node_next)->str;
    }
    join = ft_strjoin(str1, str2);
    new_node = new_node_cmd(join, WORD, *data);
    if((!(*node)->prev && !(*node_next)->next) 
        || (!(*node)->prev && (*node_next)->next))
     {
         if (!(*node)->prev && !(*node_next)->next)
         {
             // there are only two nodes
              return ;
         }
         replace_nodes(node, node_next, &new_node);
         printf("first: %s\n", new_node->str);
         join_unspaced1(&new_node, &(new_node->next), data);
     }
    else if((*node)->prev && (*node_next)->next)
    {
       replace_nodes(node, node_next, &new_node);
        printf("second : %s\n", new_node->str);
        join_unspaced1(&new_node, &(new_node->next), data); 
    }
    else if((*node)->prev && !(*node_next)->next)
    {
         replace_nodes(node, node_next, &new_node);
          printf("last :%s\n", new_node->str);
         join_unspaced1(&new_node, &(new_node->next), data);
    }
   return ;
}













// void    join_unspaced(t_cmd   **node, t_cmd    **node_next, t_data  *data)
// {
//     char    *str1;
//     char    *str2;
//     char    *join;
//     t_cmd   *new_node;
 
//     if(!*node || !*node_next || (*node_next)->type == SPC || (*node)->type == SPC)
//         return ;
//     if (check_one(*node, *node_next))
//     {
//         printf("in fucntion\n");
//         str1 = trim_quote((*node)->str);
//         str2 = trim_quote((*node_next)->str);
        
//     }
//     // join = (*node_next)->str;
//     // // printf("its first mdoe %zu |  %s\n", ft_strlen(str), str);
//     // if ((*node_next)->type == D_QUOTES || (*node_next)->type == S_QUOTES)
//     //     join = rmv_quotes(join);
//     join = ft_strjoin(str1, str2);
//     new_node = new_node_cmd(join, WORD, data);
//     if(!(*node)->prev && !(*node_next)->next)
//         return (data->cmd = new_node, (void)0);
//     else if(!(*node)->prev && (*node_next)->next)
//     {
//         printf("in last condition\n");
//         (*node_next)->next->prev = new_node;
//         new_node->next = (*node_next)->next;
//         (*node) = new_node;
//         if((*n_next)->type == WORD && )
//         return;
//     }
//     else if (!(*node_next)->next && (*node)->prev)
//         return ((*node)->prev->next = new_node, (void)0);
//     else if((*node_next)->next && (*node)->prev)
//     {
//         (*node)->prev->next = new_node;
//         (*node_next)->next->prev = new_node;
//          new_node->next = (*node_next)->next;
//         (*node_next) = new_node;
//         return ;
//     }
//     return ;
// }

