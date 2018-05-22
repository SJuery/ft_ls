/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:38:38 by sjuery            #+#    #+#             */
/*   Updated: 2018/05/21 19:28:07 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			handle_error(char *error_type)
{
	ft_putstr(error_type);
	exit(0);
}

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
			// printf("%s\n", (char *)vector_get(&vector, i));
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

void ft_ls(t_ls *ls, char *dir_name)
{
	DIR 			*dir;
	struct dirent 	*cdir;
	char 			*recurseDir;
	t_vector 			vector;
	struct s_queue	*queue;

	queue = queueInit();
	printf("%s:\n", dir_name);
	if(!(dir = opendir(dir_name)))
		handle_error("Couldn't open directory\n");
	vector_init(&vector);
	while((cdir = readdir(dir)))
		vector_add(&vector, ft_strdup(cdir->d_name));
	quicksort(vector, 0, vector.total - 1);
	for (int i = 0; i < vector.total; i++)
	{
		struct stat path_stat;
		char *currentFile = (char *)vector_get(&vector, i);

		stat(ft_strjoin(dir_name, currentFile), &path_stat);
		if(S_ISDIR(path_stat.st_mode) && currentFile[0] != '.' && ls->flag_recursive)
			enqueue(queue, currentFile);
		if(currentFile[0] != '.')
			printf("%s\t", currentFile);
	}
	printf("\n");
	while((recurseDir = dequeue(queue)))
		ft_ls(ls, ft_strjoin(ft_strjoin(dir_name, recurseDir), "/"));
}

int main(int argc, char **argv) {
	t_ls			*ls;

	ls = (struct s_ls *)malloc(sizeof(t_ls));
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
			if(argv[i][0] == '-')
				for(int j = 1; j < ft_strlen(argv[i]); j++)
				{
					if(argv[i][j] == 'R')
						ls->flag_recursive = 1;
					else if(argv[i][j] == 'r')
						ls->flag_reverse = 1;
					else if(argv[i][j] == 't')
						ls->flag_time = 1;
					else if(argv[i][j] == 'a')
						ls->flag_all = 1;
					else if(argv[i][j] == 'l')
						ls->flag_long = 1;
				}
		ft_ls(ls, argv[argc - 1]);
	}
	else
		ft_ls(ls, "./");
	return 0;
}
