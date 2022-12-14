/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszklarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 08:58:59 by dszklarz          #+#    #+#             */
/*   Updated: 2021/09/13 11:24:36 by dszklarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/*structures*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*basic*/

int		ft_isalnum(int	c);
int		ft_isdigit(int	c);
int		ft_isprint(int	c);
int		ft_isalpha(int	c);
int		ft_isascii(int	c);
int		ft_tolower(int	c);
int		ft_toupper(int	c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

/*memory*/

int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t	n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void	*dst, const void *src, size_t n);
void	*ft_memset(void	*b, int	c, size_t	len);
void	ft_bzero(void	*s, size_t	n);

/*strings*/

int		ft_strncmp(const char	*s1, const char	*s2, size_t	n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strcpy(char *dest, char *src);

/*lists*/

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*others*/

void	*ft_calloc(size_t count, size_t size);

/*printf*/

int	ft_printf(const char *str, ...);
int	ft_read(const char *str, va_list list);
int	ft_put(char c, va_list list);

/*Put-functions*/

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(long int n);
int	ft_putuint(unsigned long int n);
int	ft_puthex(unsigned long int n, char *str);
int	ft_putpointer(unsigned long int n, char *str);
long int get_padding(const char* str);
size_t get_argc(const char *str);
size_t compute_padding(size_t size, size_t padding);
size_t measure_output(const char* str, size_t ac, va_list list);
size_t measure_int(long long int nbr);
size_t measure_unsigned(unsigned long long int nbr);
size_t measure_hex(unsigned long long int nbr);
size_t get_token_length(const char* str);
size_t count_arg_len(va_list list, char token);
size_t write_formated(char* buffer, va_list list, char token, int padding);
size_t abs_value(long int nbr);
int format_string(const char* str, va_list list, char* buffer);

#endif