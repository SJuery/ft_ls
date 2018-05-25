/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:41 by sjuery            #+#    #+#             */
/*   Updated: 2018/05/24 17:44:25 by sjuery           ###   ########.fr       */
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
	unsigned int		flag_one;
	unsigned int		flag_recursion;
	unsigned int		flag_reverse;
	unsigned int		flag_all;
	unsigned int		flag_long;
	unsigned int		flag_time;
}							t_ls;

//Sorting

void quicksort(t_vector vector, int p, int len);
int partition(t_vector vector, int p, int r);
