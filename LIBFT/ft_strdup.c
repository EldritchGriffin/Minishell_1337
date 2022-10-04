/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:32:13 by zrabhi            #+#    #+#             */
/*   Updated: 2022/10/04 00:49:44 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*src;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	src = (char *)malloc(sizeof(char) * (len + 1));
	if(!*src)
		return (src[0] = '\0', src);
	if (!src)
		return (NULL);
	while (s1[i])
	{
		src[i] = s1[i];
		i++;
	}
	src[i] = '\0';
	return (src);
}
