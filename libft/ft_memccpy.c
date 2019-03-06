/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:57:31 by osloboda          #+#    #+#             */
/*   Updated: 2018/10/30 19:35:30 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *destination,
		const void *source, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char*)destination;
	s = (unsigned char*)source;
	i = -1;
	while (++i < n)
	{
		d[i] = s[i];
		if ((unsigned char)s[i] == (unsigned char)c)
			return (destination + i + 1);
	}
	return (NULL);
}
