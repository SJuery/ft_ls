/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:42:34 by sjuery            #+#    #+#             */
/*   Updated: 2018/05/21 19:26:10 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>
# define EXCEPT !exc ? i + 2 : i
# define SHARP (prtf->sharp ? 1 + i : i)
# define BUFF_SIZE 1

typedef struct 				s_vector
{
    void 					**items;
    int 					capacity;
    int 					total;
} 							t_vector;

typedef struct 				s_item {
  char          			*dir;
  struct 					s_item *next;
}							t_item;

typedef struct 				s_stack {
							struct s_item *item;
}							t_stack;

typedef struct 				s_node
{
	char 					*dir;
	struct s_node 			*next;
}							t_node;

typedef struct 				s_queue
{
	struct s_node 			*first;
	struct s_node 			*last;
}							t_queue;

typedef union				u_values
{
	char					c;
	char					*cp;
	int						i;
	long int				li;
	long long int			lli;
	unsigned long long int	ulli;
}							t_values;

typedef struct				s_printf
{
	int						len;
	int						ret;
	int						minus;
	int						plus;
	int						sharp;
	int						space;
	int						zero;
	int						size;
	int						precise;
	int						precision;
	int						hh;
	int						h;
	int						ll;
	int						l;
	int						j;
	int						z;
	char					spec;
	char					*tmpstr;
	char					*str;
	char					c;
	long long int			arg;
	t_values				uvals;
}							t_printf;

typedef	struct				s_fpointer
{
	int						(*converter[126])(va_list args, t_printf *prtf);
}							t_fpointer;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_printf(const char *format, ...);
int					parse_input(va_list args, t_printf *prtf,
											t_fpointer *fptr);
char				*ft_itoa_base(unsigned long long int value,
											int base, int lowercase);
int					parse_flags(char *orgstr, t_printf *prtf);
void				flags_to_converter(t_fpointer *fptr);
int					parse_per(va_list args, t_printf *prtf);
int					print_ints(char *arg, t_printf *prtf, int octa);
int					print_sints(long long int arg,
											t_printf *prtf);
int					ft_print_unsigned_o_number(char *arg,
											t_printf *prtf);
int					parse_str(va_list args, t_printf *prtf);
int					parse_deci(va_list args, t_printf *prtf);
int					parse_char(va_list args, t_printf *prtf);
int					parse_octa(va_list args, t_printf *prtf);
int					parse_hexa(va_list args, t_printf *prtf);
int					parse_udeci(va_list args, t_printf *prtf);
int					print_char(char arg, t_printf *prtf);
int					print_str(t_printf *prtf);
char				*conv_octa(t_printf *prtf);
char				*conv_hexa(t_printf *prtf);
int					zero_minus_space(int size, char c, char zms);
char				*ft_strjoin_c(char c);
void				ft_putstr_n(char *s, int start, int len);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strnew(size_t size);
char				*conv_uni(wchar_t arg);
int					print_per(va_list pargs, t_printf *prtf);
int					size_sints(long long int arg, t_printf *prtf,
											int excep);

int					get_next_line(const int fd, char **line);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));
int					ft_isnumber(char *str);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_itoa_base(unsigned long long int value,
					int base, int lowercase);
int					ft_intlen(long long int n);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *str, int val, size_t len);

char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
int					ft_widelen(wchar_t arg);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_swap(int *a, int *b);

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(long long int n);
void				ft_putnbr_fd(long long int n, int fd);
void				ft_putunbr(unsigned long long int n);
void				ft_putnstr(char *s, int i, int len);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);

int					ft_wordcount(char const *s, char c);
size_t				ft_numcount(int n);

//Queue

struct s_queue *queueInit();
void enqueue(struct s_queue *queue, char *dir);
char *peek(struct s_queue *queue);
char *dequeue(struct s_queue *queue);
int isEmpty(struct s_queue *queue);

//Stack

struct s_stack *stackInit(void);
void stackPush(struct s_stack *stack, char *dir);
char *stackPop(struct s_stack *stack);

//Vectors

void vector_init(t_vector *);
int vector_total(t_vector *);
static void vector_resize(t_vector *, int);
void vector_add(t_vector *, void *);
void vector_set(t_vector *, int, void *);
void *vector_get(t_vector *, int);

#endif
