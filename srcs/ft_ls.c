/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:38 by sjuery            #+#    #+#             */
/*   Updated: 2018/05/30 20:15:00 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int partition(t_vector vector, int p, int r)
{
	int i = p, j = r;
	char *pivot;
	char *temp;

	pivot = vector_get(&vector, p);

	while (1)
	{
		while (ft_strcmp(vector_get(&vector, i), pivot) < 0)
			i++;
		while (ft_strcmp(vector_get(&vector, j), pivot) > 0)
			j--;
		if (i < j)
		{
			temp = vector_get(&vector, i);
			vector_set(&vector, i, vector_get(&vector, j));
			vector_set(&vector, j, temp);
			if (ft_strcmp(vector_get(&vector, i), vector_get(&vector, j)) == 0)
				j--;
		}
		else
			return j;
	}
}

void quicksort(t_vector vector, int p, int len)
{
	int q;

	if (p < len)
	{
		q = partition(vector, p, len);
		quicksort(vector, p, q);
		quicksort(vector, q + 1, len);
	}
}

char *permissions(struct stat fileStat)
{
	char *permissions;

	permissions = ft_memalloc(sizeof(char) * 10 + 1);
	if(S_ISDIR(fileStat.st_mode))
		permissions[0] = 'd';
	else if(S_ISLNK(fileStat.st_mode))
		permissions[0] = 'l';
	else if(S_ISSOCK(fileStat.st_mode))
		permissions[0] = 's';
	else if(S_ISBLK(fileStat.st_mode))
		permissions[0] = 'b';
	else if(S_ISFIFO(fileStat.st_mode))
		permissions[0] = 'p';
	else if(S_ISCHR(fileStat.st_mode))
		permissions[0] = 'c';
	else
		permissions[0] = '-';
	permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
	permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
	permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
	permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
	permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
	permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
	permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
	permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
	return(permissions);
}

void ft_ls(t_ls *ls)
{
	DIR				*dir;
	struct dirent	*cdir;
	t_vector		vector;
	char			*pop;
    // 
	// if(pop = stackPop(ls->stack))

	while((pop = stackPop(ls->stack)))
	{
		printf("%s:\n", pop);
		if(!(dir = opendir(pop)))
		{
			perror("ft_ls");
			continue ;
		}
		vector_init(&vector);
		while((cdir = readdir(dir)))
			vector_add(&vector, ft_strdup(cdir->d_name));
		quicksort(vector, 0, vector.total - 1);
		for (int i = 0; i < vector.total; i++)
		{
			struct stat path_stat;
			struct stat fileStat;
			char *recurseFile = (char *)vector_get(&vector, vector.total - i - 1);
			char *printFile = (char *)vector_get(&vector, i);
			lstat(ft_strjoin(ft_strjoin(pop, "/"), recurseFile), &path_stat);
			if(printFile[0] != '.')
			{
				lstat(ft_strjoin(ft_strjoin(pop, "/"), printFile), &fileStat);
				ft_printf("%s  %d %s  %s %7lld %.24s", permissions(fileStat), fileStat.st_nlink, getpwuid(fileStat.st_uid)->pw_name, getgrgid(fileStat.st_gid)->gr_name, fileStat.st_size, ctime(&fileStat.st_mtimespec.tv_sec));
				printf(" %s\n", printFile);
			}
			if(S_ISDIR(path_stat.st_mode) && recurseFile[0] != '.' && ls->flag_recursion)
				stackPush(ls->stack, ft_strjoin(pop, ft_strjoin("/", recurseFile)));
		}
		closedir(dir);
	}
}

int main(int argc, char **argv) {
	t_ls			*ls;
	size_t			cnt;

	ls = (struct s_ls *)ft_memalloc(sizeof(t_ls));
	ls->stack = stackInit();
	if(argv[argc-1][0] == '-' || argc == 1)
		stackPush(ls->stack, ".");
	else
		stackPush(ls->stack, argv[argc-1]);
	if(argc > 1)
	{
		while(argc-- > 1)
		{
			cnt = 0;
			if(argv[argc][0] == '-')
				while(++cnt < ft_strlen(argv[argc]))
				{
					if(argv[argc][cnt]  == '1')
						ls->flag_one = 1;
					else if(argv[argc][cnt]  == 'R')
						ls->flag_recursion = 1;
					else if(argv[argc][cnt]  == 'r')
						ls->flag_reverse = 1;
					else if(argv[argc][cnt]  == 't')
						ls->flag_time = 1;
					else if(argv[argc][cnt]  == 'a')
						ls->flag_all = 1;
					else if(argv[argc][cnt]  == 'l')
						ls->flag_long = 1;
				}
		}
	}
	ft_ls(ls);
	return 0;
}
