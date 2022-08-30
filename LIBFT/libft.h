/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelyakou <aelyakou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:25:33 by zrabhi            #+#    #+#             */
/*   Updated: 2022/08/26 02:18:21 by aelyakou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>		
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_ptr
{
	void            *ptr;
	struct  s_ptr   *next;
}				t_ptr;

int     ft_strcmp(const char *s1, const char *s2);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
char	*ft_tolower(char *c);
int		ft_toupper(int c);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
char	*ft_itoa(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_memmove(void *dst, void *src, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char	*dst, const char *src, size_t dstzie);
int		ft_lstsize(t_ptr *lst);
void	ft_lstadd_back(t_ptr **lst, t_ptr *new);
void	ft_lstadd_front(t_ptr **lst, t_ptr *new);
void	destroy(t_ptr **lst);
void    *ft_malloc(int size, t_ptr **ptrs);
void	ft_lstdelone(t_ptr *lst);
void	ft_lstiter(t_ptr *lst, void (*f)(void *));
t_ptr	*ft_lstlast(t_ptr *lst);
t_ptr	*ft_lstnew(void *content);
#endif
