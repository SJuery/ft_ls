/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:41 by sjuery            #+#    #+#             */
/*   Updated: 2018/05/21 19:25:38 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <sys/stat.h>
#include <dirent.h>


typedef struct				s_ls
{
	DIR						*dir;
	struct dirent 			*cdir;
	char					*path;
	int						flag_recursive:1;
	int 					flag_reverse:1;
	int						flag_all:1;
	int						flag_long:1;
	int 					flag_time:1;
}							t_ls;

//Sorting

void quicksort(t_vector vector, int p, int len);
int partition(t_vector vector, int p, int r);
