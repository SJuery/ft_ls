/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 15:07:56 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/24 15:20:52 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vector_init(t_vector *v)
{
	v->capacity = 4;
	v->total = 0;
	v->items = malloc(sizeof(void *) * v->capacity);
}

void	vector_add(t_vector *v, void *item)
{
	void **items;

	if (v->capacity == v->total)
	{
		items = realloc(v->items, sizeof(void *) * (v->capacity * 2));
		if (items)
		{
			v->items = items;
			v->capacity = v->capacity * 2;
		}
	}
	v->items[v->total++] = item;
}

void	vector_set(t_vector *v, int index, void *item)
{
	if (index >= 0 && index < v->total)
		v->items[index] = item;
}

void	*vector_get(t_vector *v, int index)
{
	if (index >= 0 && index < v->total)
		return (v->items[index]);
	return (NULL);
}

void	vector_delete(t_vector *v, int index)
{
	int i;

	if (index < 0 || index >= v->total)
		return ;
	free(v->items[index]);
	v->items[index] = NULL;
	i = index;
	while (i < v->total - 1)
	{
		v->items[i] = v->items[i + 1];
		v->items[i + 1] = NULL;
		i++;
	}
	v->total--;
}
