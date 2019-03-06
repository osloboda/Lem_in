/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:08:26 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/27 16:59:11 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *arr, int c, size_t n)
{
	size_t	i;
	char	*a;

	i = -1;
	a = (char*)arr;
	while (++i < n)
		if (*(a + i) == (char)c)
			return (a + i);
	return (NULL);
}
