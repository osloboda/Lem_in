/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listsfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:41:12 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/13 15:41:14 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		free_mass(char **mass)
{
	free(mass[2]);
	free(mass[1]);
	free(mass);
}

void		lstadd(t_li **alst, t_li *new)
{
	t_li	*tmp;

	if (*alst != NULL && new != NULL)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		tmp->next->prev = tmp;
	}
	else
		*alst = new;
}

t_li		*lstnew(t_map *content, size_t content_size)
{
	t_li	*t;

	if (!(t = (t_li*)malloc(sizeof(t_li))))
		return (NULL);
	if (content != NULL)
	{
		t->content = content;
		t->content_size = content_size;
	}
	else
	{
		t->content = NULL;
		t->content_size = 0;
	}
	t->next = NULL;
	t->prev = NULL;
	return (t);
}

void		freevar(t_var *var)
{
	t_li	*r;
	t_li	*b;
	t_li	*bb;

	if (var->ways)
	{
		r = var->ways;
		while (r)
		{
			b = r->way;
			while (b)
			{
				bb = b->next;
				free(b);
				b = bb;
			}
			bb = r->next;
			free(r);
			r = bb;
		}
	}
	free(var);
}

void		freelst(t_var *var, t_map *map)
{
	t_map	*m;
	t_map	*tmp;
	t_rst	*t;

	m = map;
	freevar(var);
	while (m)
	{
		tmp = m->next;
		free(m->name);
		while (m->link)
		{
			t = m->link->next;
			free(m->link);
			m->link = t;
		}
		free(m);
		m = tmp;
	}
}
