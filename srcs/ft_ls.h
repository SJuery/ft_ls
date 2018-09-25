/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:41 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/24 20:10:50 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
# include <sys/stat.h>
# include <grp.h>
# include <pwd.h>
# include <dirent.h>

typedef struct			s_ls
{
	DIR					*dir;
	size_t				cnt;
	struct dirent		*cd;
	char				*test;
	char				*othertest;
	char				*othertests;
	char				*tmpstr;
	t_vector			vector;
	char				*cf;
	int					mtol;
	struct s_stack		*stack;
	char				*vec_chr;
	char				*buf;
	ssize_t				bufs;
	long long int		blocks;
	struct stat			ps;
	struct stat			fs;
	char				*rf;
	char				*pf;
	unsigned short int	f_one;
	unsigned short int	f_recursion;
	unsigned short int	f_reverse;
	unsigned short int	f_all;
	unsigned short int	f_long;
	unsigned short int	f_time;
	int					i;
	int					j;
	struct stat			ptime;
	struct stat			itime;
	struct stat			jtime;
	char				*temp;

}						t_ls;

void					quicksort(t_vector vector, int p, int len, t_ls *ls);
char					*join_path(char *rf, t_ls *ls);
char					*perm(struct stat fs);
#endif
