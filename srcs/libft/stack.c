/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:17:36 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/24 14:52:06 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_stack	*stackinit(void)
{
	struct s_stack *stack;

	stack = (struct s_stack *)malloc(sizeof(struct s_stack));
	stack->item = NULL;
	return (stack);
}

void			stackpush(struct s_stack *stack, char *dir)
{
	struct s_item *item;

	item = (struct s_item *)malloc(sizeof(struct s_item));
	item->dir = dir;
	item->next = stack->item;
	stack->item = item;
}

char			*stackpop(struct s_stack *stack)
{
	struct s_item	*item;
	char			*dir;

	item = stack->item;
	if (!stack->item)
		return (NULL);
	stack->item = item->next;
	dir = item->dir;
	free(item);
	return (dir);
}
