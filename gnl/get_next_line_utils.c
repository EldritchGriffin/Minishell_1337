/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:06:43 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/14 13:07:17 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr1(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	t_vrbls	vb;
	char	*str;

	vb.i = -1;
	vb.j = -1;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = 0;
	}
	vb.len = ft_strlen1(s1) + ft_strlen1(s2);
	str = (char *)malloc(sizeof(char) * (vb.len + 1));
	if (!str)
		return (NULL);
	while (s1[++vb.i])
		str[vb.i] = s1[vb.i];
	while (s2[++vb.j])
		str[vb.i + vb.j] = s2[vb.j];
	str[vb.i + vb.j] = '\0';
	free(s1);
	return (str);
}
