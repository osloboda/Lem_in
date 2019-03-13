/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:36:20 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/13 18:36:23 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		ftlstadd(t_bist **alst, t_bist *new)
{
	t_bist	*tmp;

	if (alst != NULL && new != NULL)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_bist		*ftlstnew(char *content, size_t content_size)
{
	t_bist	*t;

	if (!(t = (t_bist*)malloc(sizeof(t_bist))))
		return (NULL);
	if (content != NULL)
	{
		t->content = (void *)content;
		t->content_size = content_size;
	}
	else
	{
		t->content = NULL;
		t->content_size = 0;
	}
	t->next = NULL;
	return (t);
}
