#include "../headers/minishell.h"
#include "../LIBFT/libft.h"

//Testing purposes again...
static  void    print_cmd(t_cmd *cmd)
{
    while(cmd)
    {
        printf("string is [%s] ------ token value is [%d]\n",cmd->str, cmd->type);
        cmd = cmd->next;
    }
}

void    ft_shell(t_data *data, t_env *env)
{
	char	*line;
	
	while (1)
	{
		line = readline("Minishell$ ");
		add_history(line);
		build_token_list(line, data);
		print_cmd(data->cmd);
		identify_builtin(data);
		destroy(&data->ptrs);   // it cause sgmentation fault,
		data->cmd = NULL; 
	}
}
