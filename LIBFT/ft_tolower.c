/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:40:34 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/30 08:59:24 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolower(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] >= 65 && c[i] <= 90)
			c[i] += 32;
	}
	return (c);
}
