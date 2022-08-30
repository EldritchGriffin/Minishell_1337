#include "../../headers/minishell.h"


void    syntax_error(void)
{
    ft_putstr_fd("Minishell : parse error near \n", STDERR);
}

void    quotes_error(char c)
{
    ft_putstr_fd("Minishell , unclosed quotes\n", STDERR);
}

void    unexpected_token(char c)
{
    //   printf("Minishell: syntax error near\
    //     unexpected token `%c' \n", c);
        ft_putstr_fd("Minishell: syntax error near\
         unexpexted token `\"\n", STDERR);
}