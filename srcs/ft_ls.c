/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:38 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/16 22:09:11 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*perm(struct stat fs)
{
	static char	p[11];

	MATCH(S_ISDIR(fs.st_mode), p[0] = 'd');
	OR(S_ISLNK(fs.st_mode), p[0] = 'l');
	OR(S_ISSOCK(fs.st_mode), p[0] = 's');
	OR(S_ISBLK(fs.st_mode), p[0] = 'b');
	OR(S_ISFIFO(fs.st_mode), p[0] = 'p');
	OR(S_ISCHR(fs.st_mode), p[0] = 'c');
	OTHERWISE(p[0] = '-');
	p[1] = (fs.st_mode & S_IRUSR) ? 'r' : '-';
	p[2] = (fs.st_mode & S_IWUSR) ? 'w' : '-';
	p[3] = (fs.st_mode & S_IXUSR) ? 'x' : '-';
	p[4] = (fs.st_mode & S_IRGRP) ? 'r' : '-';
	p[5] = (fs.st_mode & S_IWGRP) ? 'w' : '-';
	p[6] = (fs.st_mode & S_IXGRP) ? 'x' : '-';
	p[7] = (fs.st_mode & S_IROTH) ? 'r' : '-';
	p[8] = (fs.st_mode & S_IWOTH) ? 'w' : '-';
	p[9] = (fs.st_mode & S_IXOTH) ? 'x' : '-';
	if (fs.st_mode & S_ISUID)
		p[3] = (fs.st_mode & S_IXUSR) ? 's' : 'S';
	if (fs.st_mode & S_ISGID)
		p[6] = (fs.st_mode & S_IXGRP) ? 's' : 'S';
	if (fs.st_mode & S_ISVTX)
		p[9] = (fs.st_mode & S_IXOTH) ? 't' : 'T';
	return (p);
}

void	print_ls(t_ls *ls)
{
	if (ls->flag_long)
	{
		lstat(ft_strjoin(ft_strjoin(ls->cf, "/"), ls->pf), &ls->fs);
		ft_printf("%s  %d %s  %s %7lld %.24s", perm(ls->fs),
				ls->fs.st_nlink, getpwuid(ls->fs.st_uid)->pw_name,
				getgrgid(ls->fs.st_gid)->gr_name, ls->fs.st_size,
				ctime(&ls->fs.st_mtimespec.tv_sec));
		printf(" %s", ls->pf);
		ls->bufs = ls->fs.st_size + 1;
		ls->buf = malloc(ls->bufs);
		readlink(ft_strjoin(ft_strjoin(ls->cf, "/"), ls->pf),
												ls->buf, ls->bufs);
		if (ls->buf[0] != '\0')
			printf(" -> %s", ls->buf);
		printf("\n");
	}
	else
	{
		printf("%s", ls->pf);
		if (ls->flag_one)
			printf("\n");
		else
			printf("\t");
	}
}

void	get_stats(t_ls *ls)
{
	int i;

	i = -1;
	if (ls->flag_long)
		printf("total %lld\n", ls->blocks);
	while (++i < ls->vector.total)
	{
		ls->rf = (char *)vector_get(&ls->vector, ls->vector.total - i - 1);
		ls->pf = (char *)vector_get(&ls->vector, i);
		lstat(ft_strjoin(ft_strjoin(ls->cf, "/"), ls->rf), &ls->ps);
		print_ls(ls);
		if (S_ISDIR(ls->ps.st_mode) && ls->flag_recursion)
			stackPush(ls->stack, ft_strjoin(ls->cf, ft_strjoin("/", ls->rf)));
	}
	closedir(ls->dir);
	printf("\n");
}

void	ft_ls(t_ls *ls)
{
	while ((ls->cf = stackPop(ls->stack)))
	{
		printf("%s:\n", ls->cf);
		if (!(ls->dir = opendir(ls->cf)))
		{
			perror("ft_ls");
			continue ;
		}
		vector_init(&ls->vector);
		ls->blocks = 0;
		while ((ls->cd = readdir(ls->dir)))
		{
			if (!ls->flag_all)
			{
				if (ls->cd->d_name[0] != '.')
					vector_add(&ls->vector, ft_strdup(ls->cd->d_name));
			}
			else
				vector_add(&ls->vector, ft_strdup(ls->cd->d_name));
			lstat(ft_strjoin(ft_strjoin(ls->cf, "/"), ls->cd->d_name), &ls->ps);
			ls->blocks += ls->ps.st_blocks;
		}
		quicksort(ls->vector, 0, ls->vector.total - 1);
		get_stats(ls);
	}
}

int		main(int argc, char **argv)
{
	t_ls			*ls;
	size_t			cnt;

	ls = (struct s_ls *)ft_memalloc(sizeof(t_ls));
	ls->stack = stackInit();
	if (argv[argc - 1][0] == '-' || argc == 1)
		stackPush(ls->stack, ".");
	else
		stackPush(ls->stack, argv[argc - 1]);
	if (argc > 1)
		while (argc-- > 1)
		{
			cnt = 0;
			if (argv[argc][0] == '-')
				while (++cnt < ft_strlen(argv[argc]))
				{
					MATCH(argv[argc][cnt] == '1', ls->flag_one = 1);
					OR(argv[argc][cnt] == 'R', ls->flag_recursion = 1);
					OR(argv[argc][cnt] == 'r', ls->flag_reverse = 1);
					OR(argv[argc][cnt] == 't', ls->flag_time = 1);
					OR(argv[argc][cnt] == 'a', ls->flag_all = 1);
					OR(argv[argc][cnt] == 'l', ls->flag_long = 1);
				}
		}
	ft_ls(ls);
}
