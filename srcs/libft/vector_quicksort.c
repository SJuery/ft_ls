/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_quicksort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 19:26:14 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/16 19:27:26 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int partition(t_vector vector, int p, int r)
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
