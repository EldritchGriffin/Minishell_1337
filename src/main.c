#include "../headers/minishell.h"


//TODO main function will have all our structs assigned into t_data
int main(int ac, char **av, char    **envp)
{
    (void)ac;
    (void)av;
    t_data  data;
    t_ptr   *ptrs = NULL;
    t_env   *env = NULL;
    
    data.cmd = NULL;
    data.ptrs = ptrs;
    data.cmd  =NULL;
    env = env_list(envp);
    data.env = env;
    // print_env(env);
     ft_shell(&data, env);
}
