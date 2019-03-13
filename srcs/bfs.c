/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:38:43 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/13 15:38:46 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_map		*pop_queue(t_li **queue)
{
	t_li	*last;
	t_map	*room;

	room = NULL;
	if (*queue)
		room = (*queue)->content;
	last = *queue;
	(*queue) = (*queue)->next;
	free(last);
	return (room);
}

void		queuefree(t_li *wait)
{
	t_li	*tmp;

	while (wait)
	{
		tmp = wait->next;
		free(wait);
		wait = tmp;
	}
}

int			dop_bfs(t_var *data, int uniq_bfs, t_li **queue)
{
	if (data->ways && data->ways->way->next->content == data->end)
		return (1);
	lstadd(&*queue, lstnew(data->start, 0));
	data->start->visited = uniq_bfs;
	return (0);
}

int			bfs2(t_var *data, int uniq_bfs, t_li *queue, int flag)
{
	t_rst	*tmp;
	t_map	*tmpr;

	if (dop_bfs(data, uniq_bfs, &queue))
		return (0);
	while (queue != NULL && !flag)
	{
		tmpr = pop_queue(&queue);
		tmp = tmpr->link;
		while (tmp && !flag)
		{
			if (tmp->room->visited != uniq_bfs && tmp->room->locked
			!= 1 && tmp->room != data->locked)
			{
				tmp->room->prev = tmpr;
				tmp->room->visited = uniq_bfs;
				lstadd(&queue, lstnew(tmp->room, 0));
				if (tmp->room == data->end)
					flag = 1;
			}
			tmp = tmp->next;
		}
	}
	queuefree(queue);
	return (flag);
}

int			error(char *line, t_var *var, t_map *map, t_bist *lins)
{
	if (line)
		ft_strdel(&line);
	ft_printf("ERROR\n");
	lines(lins, 0);
	freelst(var, map);
	return (1);
}
