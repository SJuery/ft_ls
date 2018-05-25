/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 17:34:56 by sjuery            #+#    #+#             */
/*   Updated: 2018/05/24 18:12:35 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv) {
	t_ls			*ls;

	ls = (struct s_ls *)ft_memalloc(sizeof(t_ls));

	int One_Recusive = 0000000011;
	if(One_Recusive & ls->flag_one && One_Recusive & ls->flag_recursion && One_Recusive & ls->flag_time)
		printf("%s\n", "One Recusive");
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
			if(argv[i][0] == '-')
				for(int j = 1; j < ft_strlen(argv[i]); j++)
				{
					if(argv[i][j] == '1')
						ls->flag_one = 0x1;
					else if(argv[i][j] == 'R')
						ls->flag_recursion = 0x2;
					else if(argv[i][j] == 'r')
						ls->flag_reverse = 0x4;
					else if(argv[i][j] == 'a')
						ls->flag_all = 0x8;
					else if(argv[i][j] == 't')
						ls->flag_time = 0x16;
					else if(argv[i][j] == 'l')
						ls->flag_long = 0x32;
				}
		printf("%d\n", ls->flag_one | ls->flag_recursion | ls->flag_reverse | ls->flag_all | ls->flag_time | ls->flag_long);
		// ft_ls(ls, argv[argc - 1]);
	}
	// else
	// 	ft_ls(ls, "./");
	return 0;
}
