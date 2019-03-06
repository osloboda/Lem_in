/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:04:14 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/27 16:55:46 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;

	i = -1;
	d = (char *)dst;
	if (dst < src)
		while (++i < n)
			*(d + i) = *((char*)src + i);
	else
		while (n--)
			*(d + n) = *((char*)src + n);
	return (dst);
}
