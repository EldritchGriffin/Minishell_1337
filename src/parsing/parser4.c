/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 10:34:04 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/21 21:45:17 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	**free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	ft_words(const char *s, char *c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c[0] && s[i + 1] == c[0]) || (s[i] != c[0] && s[i + 1] == '\0'))
			words++;
	i++;
	}
	return (words);
}

static char	**ft_cat(char **str, const char *s, char *c, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < len)
	{
		k = 0;
		while (s[j] && s[j] == c[0])
			j++;
		while (s[j] && s[j] != c[0])
		{
			str[i][k] = s[j];
			j++;
			k++;
		}
	str[i][k] = '\0';
	i++;
	}
	str[i] = 0;
	return (str);
}

typedef struct vrb
{
	int		i;
	int		j;
	int		k;
	int		len;
}	t_vrb;

char	**i_split(const char *s, char *c)
{
	char	**str;
	t_vrb	vb;

	if (!s)
		return (NULL);
	vb.len = ft_words(s, c);
	vb.i = -1;
	str = (char **)malloc(sizeof(char *) * (vb.len + 1));
	if (!str)
		return (NULL);
	vb.j = 0;
	while (++vb.i < vb.len)
	{
		vb.k = 0;
		while (s[vb.j] && s[vb.j] == c[0])
			vb.j++;
		while (s[vb.j] && s[vb.j++] != c[0])
			vb.k++;
		str[vb.i] = (char *)malloc(sizeof(char) * (vb.k + 1));
		if (!str[vb.i])
			return (free_str(str));
	}
	return (ft_cat(str, s, c, vb.len));
}