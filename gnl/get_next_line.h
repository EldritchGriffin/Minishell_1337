/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrabhi <zrabhi@student.1337.ma >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:15:14 by zrabhi            #+#    #+#             */
/*   Updated: 2022/09/14 13:06:01 by zrabhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFFER_SIZE 1

typedef struct vrbls {
	size_t	len;
	int		i;
	int		j;
}	t_vrbls;
size_t	ft_strlen1(char *str);
char	*get_next_line(int fd);
int		ft_strchr1(char *str);
char	*ft_strjoin1(char *s1, char *s2);
#endif
