/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 13:26:47 by sjuery            #+#    #+#             */
/*   Updated: 2018/09/24 14:44:46 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_queue	*queueinit(void)
{
	struct s_queue *queue;

	queue = (struct s_queue *)malloc(sizeof(struct s_queue));
	queue->first = NULL;
	queue->last = NULL;
	return (queue);
}

void			enqueue(struct s_queue *queue, char *dir)
{
	struct s_node *msg;

	msg = (struct s_node *)malloc(sizeof(struct s_node));
	msg->dir = dir;
	msg->next = NULL;
	if (!queue->first && !queue->last)
	{
		queue->first = msg;
		queue->last = msg;
	}
	else
	{
		queue->last->next = msg;
		queue->last = msg;
	}
}

char			*peek(struct s_queue *queue)
{
	if (!queue->first && !queue->last)
		return (NULL);
	return (queue->first->dir);
}

char			*dequeue(struct s_queue *queue)
{
	struct s_node *node;

	node = queue->first;
	if (!queue->first && !queue->last)
		return (NULL);
	if (queue->first == queue->last)
		queue->last = NULL;
	queue->first = node->next;
	return (node->dir);
}

int				isempty(struct s_queue *queue)
{
	if (!queue->first && !queue->last)
		return (1);
	return (0);
}
