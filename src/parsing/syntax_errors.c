/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:20 by zrabhi            #+#    #+#             */
/*   Updated: 2022/08/31 13:54:21 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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