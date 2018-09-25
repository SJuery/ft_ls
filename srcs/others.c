/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:26:14 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/24 16:51:55 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*perm(struct stat fs)
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

char		*join_path(char *rf, t_ls *ls)
{
	ls->test = ft_strjoin(ls->cf, "/");
	ls->tmpstr = ft_strjoin(ls->test, rf);
	free(ls->test);
	return (ls->tmpstr);
}

static int	compare(t_vector vector, int v1, int v2, t_ls *ls)
{
	struct stat	sv1;
	struct stat sv2;

	if (ls->flag_time)
	{
		stat(join_path(vector_get(&vector, v1), ls), &sv1);
		free(ls->tmpstr);
		stat(join_path(vector_get(&vector, v2), ls), &sv2);
		free(ls->tmpstr);
		if (sv1.st_mtime > sv2.st_mtime)
			return (1);
		else if (sv1.st_mtime < sv2.st_mtime)
			return (0);
		else
			return (2);
	}
	if (ft_strcmp(vector_get(&vector, v1), vector_get(&vector, v2)) < 0)
		return (1);
	else if (ft_strcmp(vector_get(&vector, v1), vector_get(&vector, v2)) > 0)
		return (0);
	return (2);
}

static int	partition(t_vector vector, int p, int r, t_ls *ls)
{
	int		i;
	int		j;
	char	*temp;

	i = p;
	j = r;
	while (1)
	{
		while (compare(vector, i, p, ls) == 1)
			i++;
		while (compare(vector, p, j, ls) == 1)
			j--;
		if (i < j)
		{
			temp = vector_get(&vector, i);
			vector_set(&vector, i, vector_get(&vector, j));
			vector_set(&vector, j, temp);
			if (compare(vector, i, j, ls) == 2)
				j--;
		}
		else
			return (j);
	}
}

void		quicksort(t_vector vector, int p, int len, t_ls *ls)
{
	int q;

	if (p < len)
	{
		q = partition(vector, p, len, ls);
		quicksort(vector, p, q, ls);
		quicksort(vector, q + 1, len, ls);
	}
}
