/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 21:52:56 by osloboda          #+#    #+#             */
/*   Updated: 2018/11/02 19:16:25 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*cp;
	t_list	*gg;

	if (!lst || !f)
		return (NULL);
	res = NULL;
	while (lst)
	{
		if ((cp = f(lst)))
		{
			if (res == NULL)
			{
				res = cp;
				gg = cp;
			}
			else
			{
				gg->next = cp;
				gg = gg->next;
			}
		}
		lst = lst->next;
	}
	return (res);
}
