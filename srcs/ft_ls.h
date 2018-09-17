/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:41 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/16 22:00:00 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <dirent.h>


typedef struct				s_ls
{
	DIR						*dir;
	struct dirent 			*cd;
	t_vector				vector;
	char					*cf;
	struct s_stack			*stack;
	char					*buf;
	ssize_t					bufs;
	long long int			blocks;
	struct stat 			ps;
	struct stat 			fs;
	char 					*rf;
	char 					*pf;
	unsigned short int		flag_one;
	unsigned short int		flag_recursion;
	unsigned short int		flag_reverse;
	unsigned short int		flag_all;
	unsigned short int		flag_long;
	unsigned short int		flag_time;
}							t_ls;
