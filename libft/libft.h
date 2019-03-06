/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:54:43 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/04 13:14:48 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include "get_next_line.h"
# include <unistd.h>
# include <string.h>
# include "stdarg.h"

# define RED(string) "\x1b[31m" string "\x1b[0m"
# define BRED(string) "\x1b[1;31m" string "\x1b[0m"
# define GREEN(string) "\x1b[0;32m" string "\x1b[0m"
# define BGREEN(string) "\x1b[1;32m" string "\x1b[0m"
# define YELLOW(string) "\x1b[0;33m" string "\x1b[0m"
# define BYELLOW(string) "\x1b[01;33m" string "\x1b[0m"
# define BLUE(string) "\x1b[0;34m" string "\x1b[0m"
# define BBLUE(string) "\x1b[1;34m" string "\x1b[0m"
# define MAGENTA(string) "\x1b[0;35m" string "\x1b[0m"
# define BMAGENTA(string) "\x1b[1;35m" string "\x1b[0m"
# define CYAN(string) "\x1b[0;36m" string "\x1b[0m"
# define BCYAN(string) "\x1b[1;36m" string "\x1b[0m"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
typedef struct		s_float
{
	long			whole_part;
	long			wt;
	char			*str;
	int				i;
	int				index;
	int				digit;
	int				reminder;
	int				log_value;
	int				precision;
	long double		rst;
	long double		fraction_part;
	long double		tmp1;
	long double		tmp;
}					t_float;

char				*freedom(char *a, char *b);
int					ft_printf(const char *fmt, ...);
char				*cstr(char *arg, char*script, int ssize);
char				*ft_itoa_base(unsigned long long int va,
		unsigned int base, int uppercase, unsigned long long int n);
int					*check_flags(char **script,
		int *flags, char **arg, int *ssize);
char				*cre1(char *script,
		char *arg, int ssize, int *flags);
int					*get_flags(char **arg, int *flags,
		char *script, int ssize);
char				*fill(char *script, char *arg,
		int *flags, int ssize);
char				*ft_itoa2(long long int n);
char				*ft_itoa1(unsigned long long int n);
char				*dot(char *arg, char *script,
		int *precision, int ssize);
char				*di(va_list tr, char *script,
		long long int ret, int ssize);
char				*uox(va_list tr, char *script, int ssize);
char				*check_per(char *str);
double				pow(double a, double b);
char				*f_t_s(long double num, char *script);
void				ft_swap(int *a, int *b);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				*ft_memmove(void *dst, const void *src, size_t n);
char				*ft_strdup(const char *src);
char				*ft_strnstr(const char *haystack, const
		char *needle, size_t len);
int					ft_isprint(int c);
void				*ft_memset(void *b, int c, size_t len);
size_t				ft_strlcat(char *dst,
		const char *src, size_t dstsize);
char				*ft_strrchr(const char *s, int c);
void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *destination,
		const void *source, int c, size_t n);
char				*ft_strcat(char *s1, const char *s2);
size_t				ft_strlen(const char *str);
char				*ft_strstr(const char *haystack, const char *needle);
int					ft_isalnum(int c);
void				*ft_memchr(const void *arr, int c, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_toupper(int c);
int					ft_isascii(int c);
void				*ft_memcpy(void *destptr, const void *srcptr, size_t num);
char				*ft_strcpy(char *destptr, const char *srcptr);
char				*ft_strncpy(char *destptr, const char *srcptr, size_t num);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_new_strjoin(char *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
int					find(char *str, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_fprime(int nb);
void				ft_rev_wstr(char *str);
char				*ft_search_and_replace(char *str, char a, char b);
void				ft_print_bits(unsigned char octet);
unsigned char		ft_reverse_bits(unsigned char octet);

#endif
