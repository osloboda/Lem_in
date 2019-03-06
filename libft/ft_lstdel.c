/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 21:12:28 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/08 13:47:28 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*t;
	t_list	*ab;

	t = *alst;
	while (t)
	{
		ab = t->next;
		del(t->content, t->content_size);
		free(t);
		t = ab;
	}
	*alst = NULL;
}
