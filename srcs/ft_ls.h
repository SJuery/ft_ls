/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:41 by sjuery            #+#    #+#             */
/*   Updated: 2018/05/30 13:13:27 by sjuery           ###   ########.fr       */
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
	struct dirent 			*cdir;
	char					*path;
	struct s_stack			*stack;
	unsigned short int		flag_one;
	unsigned short int		flag_recursion;
	unsigned short int		flag_reverse;
	unsigned short int		flag_all;
	unsigned short int		flag_long;
	unsigned short int		flag_time;
}							t_ls;

//Sorting

void quicksort(t_vector vector, int p, int len);
int partition(t_vector vector, int p, int r);
