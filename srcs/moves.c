/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:40:21 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/13 15:40:26 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		store_way(t_var *var, t_map *going, t_li *w, int i)
{
	t_li	*tmp;

	lstadd(&w, lstnew(0, sizeof(t_li *)));
	var->ways = w;
	while (w && w->next)
		w = w->next;
	w->way = lstnew(going, sizeof(t_map *));
	while (going && going->prev && ++i)
	{
		if (ft_strcmp(going->prev->name, var->start->name))
			going->prev->locked = 1;
		tmp = lstnew(going->prev, sizeof(t_map *));
		tmp->next = w->way;
		w->way->prev = tmp;
		w->way = tmp;
		going = going->prev;
	}
	w->way->way_lenght = i;
}

int			connn(t_li *tmp, t_li *ww)
{
	t_li	*www;
	int		res;

	res = 0;
	www = ww;
	while (www && www->way != tmp)
	{
		res += tmp->way_lenght - www->way->way_lenght;
		www = www->next;
	}
	return (res);
}

int			mvway(t_li *cur, int i, int d, t_var *var)
{
	t_li	*tmp;
	int		flag;

	flag = 0;
	tmp = cur;
	while (tmp->next)
		tmp = tmp->next;
	tmp->content->ant = 0;
	while (tmp->prev && tmp->content->ant != i)
	{
		if (tmp->prev->content->ant)
		{
			tmp->content->ant = tmp->prev->content->ant;
			if (tmp->content != var->pinned)
				ft_printf(MAGENTA("L%i-%s "), tmp->prev->content->ant,
					tmp->content->name);
			else
				ft_printf(CYAN("L%i-%s "), tmp->prev->content->ant,
					tmp->content->name);
			flag = 1;
			tmp->prev->content->ant = 0;
		}
		tmp = tmp->prev;
	}
	return ((d == 1) ? d : flag);
}

int			print_moves(t_var *var, int flag, int *i, t_li *www)
{
	t_li	*tmp;

	tmp = var->ways;
	while (tmp && (www = tmp->way->next))
	{
		www->way_lenght = tmp->way->way_lenght;
		flag = mvway(www, var->ants - *i, flag, var);
		if (*i > 0 && *i > connn(tmp->way, var->ways) && (flag = 1))
		{
			if (www->content == var->pinned)
				ft_printf(CYAN("L%i-%s "), var->ants - *i + 1,
					www->content->name);
			else
				ft_printf(BMAGENTA("L%i-%s "), var->ants - *i + 1,
					www->content->name);
			www->content->ant = var->ants - *i + 1;
			(*i)--;
		}
		tmp = tmp->next;
	}
	if (www && www->content != var->end && flag && ++var->lines)
		ft_putstr("\n");
	return (flag);
}

void		marafon(t_var *var)
{
	int		i;
	int		flag;

	flag = 1;
	i = var->ants;
	var->lines = 1;
	while (i > 0 || flag || var->end->ant)
		flag = print_moves(var, 0, &i, 0);
	if (var->lines == 1)
		ft_putstr("\n");
	else
		var->lines -= 1;
}
