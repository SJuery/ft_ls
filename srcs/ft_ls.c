/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:38 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/24 20:12:53 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_ls(t_ls *ls)
{
	if (ls->f_long)
	{
		lstat(join_path(ft_strjoin(ls->test, ls->pf), ls), &ls->fs);
		free(ls->tmpstr);
		ft_printf("%s  %d %s  %s %7lld %.24s", perm(ls->fs),
				ls->fs.st_nlink, getpwuid(ls->fs.st_uid)->pw_name,
				getgrgid(ls->fs.st_gid)->gr_name, ls->fs.st_size,
				ctime(&ls->fs.st_mtimespec.tv_sec));
		ft_printf(" %s", ls->pf);
		ls->bufs = ls->fs.st_size + 1;
		ls->buf = malloc(ls->bufs);
		readlink(join_path(ls->pf, ls), ls->buf, ls->bufs);
		free(ls->tmpstr);
		if (ls->buf[1] != '\0')
			ft_printf(" -> %s", ls->buf);
		free(ls->buf);
		ft_printf("\n");
		return ;
	}
	ft_printf("%s", ls->pf);
	if (ls->f_one)
		ft_printf("\n");
	else
		ft_printf("\t");
}

void	get_stats(t_ls *ls)
{
	int i;

	i = -1;
	ls->f_long ? ft_printf("total %lld\n", ls->blocks) : 0;
	while (++i < ls->vector.total)
	{
		ls->mtol = 2;
		ls->pf = ls->f_reverse ? (char *)vector_get(&ls->vector,
				ls->vector.total - i - 1) : (char *)vector_get(&ls->vector, i);
		ls->rf = ls->f_reverse ? (char *)vector_get(&ls->vector, i) :
					(char *)vector_get(&ls->vector, ls->vector.total - i - 1);
		lstat(join_path(ls->rf, ls), &ls->ps);
		free(ls->tmpstr);
		print_ls(ls);
		if (S_ISDIR(ls->ps.st_mode) && ls->f_recursion
				&& ft_strcmp(ls->rf, ".") && ft_strcmp(ls->rf, ".."))
		{
			ls->othertest = ft_strjoin("/", ls->rf);
			stackpush(ls->stack, ft_strjoin(ls->cf, ls->othertest));
			free(ls->othertest);
		}
	}
	if (ls->mtol == 2 && !ls->f_long)
		ft_printf("\n");
	closedir(ls->dir);
}

void	compute_files(t_ls *ls)
{
	ls->blocks = 0;
	while ((ls->cd = readdir(ls->dir)))
	{
		lstat(join_path(ls->cd->d_name, ls), &ls->ps);
		free(ls->tmpstr);
		if (!ls->f_all)
			if (ls->cd->d_name[0] != '.')
			{
				vector_add(&ls->vector, ft_strdup(ls->cd->d_name));
				ls->blocks += ls->ps.st_blocks;
			}
		if (ls->f_all)
		{
			vector_add(&ls->vector, ft_strdup(ls->cd->d_name));
			ls->blocks += ls->ps.st_blocks;
		}
	}
}

void	ft_ls(t_ls *ls)
{
	vector_init(&ls->vector);
	while ((ls->cf = stackpop(ls->stack)))
	{
		if (ls->mtol++)
			ft_printf("\n%s:\n", ls->cf);
		if (!(ls->dir = opendir(ls->cf)))
		{
			free(ls->cf);
			perror("ft_ls");
			continue ;
		}
		compute_files(ls);
		quicksort(ls->vector, 0, ls->vector.total - 1, ls);
		get_stats(ls);
		free(ls->cf);
		while (ls->vector.total > 0)
			vector_delete(&ls->vector, ls->vector.total - 1);
	}
}

int		main(int argc, char **argv)
{
	t_ls			*ls;
	size_t			cnt;

	ls = (struct s_ls *)ft_memalloc(sizeof(t_ls));
	ls->stack = stackinit();
	if (argv[argc - 1][0] == '-' || argc == 1)
		stackpush(ls->stack, ft_strdup("."));
	else
		stackpush(ls->stack, ft_strdup(argv[argc - 1]));
	if (argc > 1)
		while (argc-- > 1)
			if (argv[argc][cnt = 0] == '-' && argv[argc][1])
				while (++cnt < ft_strlen(argv[argc]))
				{
					MATCH(argv[argc][cnt] == '1' && !ls->f_long, ls->f_one = 1);
					OR(argv[argc][cnt] == 'R', ls->f_recursion = 1);
					OR(argv[argc][cnt] == 'r', ls->f_reverse = 1);
					OR(argv[argc][cnt] == 't', ls->f_time = 1);
					OR(argv[argc][cnt] == 'a' && !ls->f_one, ls->f_all = 1);
					OR(argv[argc][cnt] == 'l', ls->f_long = 1);
				}
	ft_ls(ls);
	free(ls->vector.items);
	free(ls->stack);
	free(ls);
}
