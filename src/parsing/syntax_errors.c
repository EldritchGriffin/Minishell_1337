/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:20 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/02 16:44:17 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	syntax_error(void)
{
	ft_putstr_fd("Minishell : parse error near \n", STDERR);
}

void	quotes_error(char c)
{
	ft_putstr_fd("Minishell , unclosed quotes\n", STDERR);
}

void	unexpected_token(char c)
{
	ft_putstr_fd("Minishell: syntax error \n", 2);
}

void	mini_perror(char *str)
{
	if (!(ft_strcmp(str, "PIPE")))
		ft_putstr_fd("Minishell: syntax error near\
		unexpected token `|\"\n", STDERR);
	else if (!(ft_strcmp(str, "Memory")))
		ft_putstr_fd("Minishell: Memory error, Sorry \n", STDERR);
	else if (!(ft_strcmp(str, "SPC")))
		ft_putstr_fd("Minishell: syntax error near\
		unexpected token `newline' `\"\n", STDERR);
}
