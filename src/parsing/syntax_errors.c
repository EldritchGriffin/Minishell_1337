/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:54:20 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/25 21:37:58 by aelyakou         ###   ########.fr       */
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
	printf  ("Minishell: syntax error near\
		 unexpexted token `%c\"\n", c);
}

void	mini_perror(int type)
{
	if (type == PIPE)
		ft_putstr_fd("Minishell: syntax error near\
		 unexpected token `'", STDERR);
}
